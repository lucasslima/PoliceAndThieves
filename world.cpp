#include "world.h"
#include <string>
#include <fstream>
#include "highspeedblock.h"
#include "lowspeedblock.h"
#include "hideoutblock.h"
#include "wallblock.h"
#include "GL/gl.h"
#include "GL/glut.h"
#include <utility>
#include "block.h"
#include <iostream>
#include <typeinfo>

using std::string;
using std::ifstream;
using std::pair;

void quadrado(const Point &p)
{
    std::vector<Point> blockDrawPoints;
    blockDrawPoints.push_back(Point(p.getX(),p.getY()+2.5));
    blockDrawPoints.push_back(Point(p.getX() + 2.5, p.getY() + 2.5));
    blockDrawPoints.push_back(Point(p.getX() + 2.5,p.getY()));
    blockDrawPoints.push_back(p);
    glColor3d(0.0,0.0,0.5);
    DrawUtils::drawPoligon(blockDrawPoints);
}

World::World() {}

void World::initializeRendering()
{
    dx = 0;
    dy = 0;
    if (mStreets.size() == 0)
        return;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    mWorldHeight = mStreets.size() * Block::BLOCK_SIZE;
    mWorldWidth = mStreets[0].size() * Block::BLOCK_SIZE;
    origin = Point(0,0);
    mWorldLeft = 0;
    mWorldRight = mWorldWidth;
    mWorldBottom = 0;
    mWorldTop = mWorldHeight;
    gluOrtho2D(mWorldLeft, mWorldRight, mWorldTop, mWorldBottom);
    glMatrixMode(GL_MODELVIEW);
    Point p(origin);
    for ( int i = 0 ; i < mStreets.size(); i++){
        for (int j = 0 ; j < mStreets[i].size(); j++){
            auto b = mStreets[i][j];
            b->setCoordinates(p.getX(),p.getY());
            if (i > 0)
                b->setNorthNeighbor(mStreets[i-1][j]);
            if (j > 0)
                b->setWestNeightbor(mStreets[i][j-1]);
            if (i < mStreets.size() - 1)
                b->setSouthNeighbor(mStreets[i+1][j]);
            if (j < mStreets[i].size() - 1)
                b->setEastNeightbor(mStreets[i][j+1]);
            for (auto c = p.getX(); c <= p.getX() + Block::BLOCK_SIZE ; c++){
                for (auto d = p.getY(); d <= p.getY() + Block::BLOCK_SIZE ; d++){
                    mCurrentBlock[std::pair<int,int>(c,d)] = b;
                    mSpatialHash[std::pair<int,int>(c/32,d/32)].push_back(b);
                }
            }
            p.setX(p.getX() + Block::BLOCK_SIZE);

        }
        p.setX(origin.getX());
        p.setY(p.getY() + Block::BLOCK_SIZE);
    }
    bool found = false;
    for (auto v : mStreets){
        for (Block* b : v){
            if (!b->isSolid()){
                mThieve = b->getCoordinates();
                found = true;
                break;
            }
        }
        if (found) break;
    }
    found = false;
    for (int i = mStreets.size()-1;i >= 0 ; i--){
        for (int j = mStreets[i].size() - 1; j >= 0 ; j--){
            if (!mStreets[i][j]->isSolid()){
                mPolice = mStreets[i][j]->getCoordinates();
                mPolice.setX(mPolice.getX() + 2.5);
                mPolice.setY(mPolice.getY() + 2.5);
                found = true;
                break;
            }
        }
        if (found) break;
    }
    return;
}

void World::loadStreets(string pathToMap) {
  ifstream mapFile(pathToMap);
  if (mapFile.is_open()) {
    string line;
    while (getline(mapFile, line)) {
        bool enclosedStreet = false;
      mStreets.push_back(vector<Block *>());
      for (char c : line) {
          if (c == ' ' && enclosedStreet == false)
              continue;
          enclosedStreet = true;
        switch (c) {
        case ' ':
          mStreets.back().push_back(new HighSpeedBlock());
          break;
        case '%':
          mStreets.back().push_back(new WallBlock());
          break;
        case 'b':
          mStreets.back().push_back(new LowSpeedBlock());
          break;
        case '#':
          mStreets.back().push_back(new HideoutBlock());
          break;
        }
      }
      enclosedStreet = false;
    }
   }
}

void World::update()
{
    double oldX = mPolice.getX();
    double oldY = mPolice.getY();
    mPolice.setX(oldX + dx);
    mPolice.setY(oldY + dy);
    Block * policeBlock = mCurrentBlock[std::pair<int,int>(oldX,oldY)];
    Block * thieveBlock = mCurrentBlock[std::pair<int,int>(mThieve.getX(),mThieve.getY())];
    if (policeBlock == thieveBlock)
        std::cout << "Found thieve! "<< std::endl;
    if (typeid(*policeBlock) == typeid(HideoutBlock))
        std::cout << "Police stoped on hideout" << std::endl;

    Block * toMove = mCurrentBlock[std::pair<int,int>(mPolice.getX(),mPolice.getY())];
    if (toMove->isSolid()){
        mPolice.setX(oldX);
        mPolice.setY(oldY);
        dx = 0;
        dy = 0;
    }
    else{
        toMove = mCurrentBlock[std::pair<int,int>(mPolice.getX() + 2.5,mPolice.getY() + 2.5)];
        if (toMove->isSolid()){
            mPolice.setX(oldX);
            mPolice.setY(oldY);
            dx = 0;
            dy = 0;
        }
    }
//    std::vector<Block*>& neighbors = mSpatialHash[std::pair<int,int>(mPolice.getX()/32,mPolice.getY()/32)];
//    for (auto& b : neighbors){
//        const Point& p = b->getCoordinates();
//        if (b->isSolid()){
//            if (p.getX() < mPolice.getX() + 2.5 &&
//               p.getX() + Block::BLOCK_SIZE > mPolice.getX() &&
//               p.getY() < mPolice.getY() + 2.5 &&
//               p.getY() + Block::BLOCK_SIZE > mPolice.getY() ) {
//                std::cout << "collision detected!" << std::endl;
//                mPolice.setX(oldX);
//                mPolice.setY(oldY);
//                dx = 0;
//                dy = 0;
//                break;
//            }
//        }
//    }
    //std::cout << "Police position: " << mPolice.getX() << "," << mPolice.getY() << std::endl;
    glutPostRedisplay();
}

void World::render(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    Point pen(origin.getX(),origin.getY());
    for (std::vector<Block*> v : mStreets){
        for (Block* b : v){
            b->draw();
            pen.setX(pen.getX() + 10);
            if (b == v.back())
                pen.setX(-165);
        }
        pen.setY(pen.getY() + 10);
    }

    quadrado(mPolice);
    quadrado(mThieve);
    glFlush();
    glutSwapBuffers();
}






void World::handleInputMouse(int button, int x, int y)
{

        int widthSize =  glutGet(GLUT_WINDOW_WIDTH);
        int heightSize = glutGet(GLUT_WINDOW_HEIGHT);


        int coordinateX =  x*100 / widthSize;
        int coordinatey =  y*100 / heightSize;
        cout << button <<"  " << coordinateX<<" "<<coordinatey << "\n ";

/*
      switch (button){
    case 'w':
        if ( dy > -1){
            dx = 0;
            dy -= ACCELERATION;
        }
        break;
    case 's':
        if (dy < 1){
            dx = 0;
            dy += ACCELERATION;
        }
        break;
    case 'd':
        if (dx < 1){
            dx +=ACCELERATION;
            dy = 0;
        }
        break;
    case 'a':
        if (dx > -1){
            dy = 0;
            dx -= ACCELERATION;
        }
        break;
    default:
        break;
    }

*/


}



void World::handleInputKeyboard(char c, int x, int y)
{
    switch (c){
    case 'w':
        if ( dy > -1){
            dx = 0;
            dy -= ACCELERATION;
        }
        break;
    case 's':
        if (dy < 1){
            dx = 0;
            dy += ACCELERATION;
        }
        break;
    case 'd':
        if (dx < 1){
            dx +=ACCELERATION;
            dy = 0;
        }
        break;
    case 'a':
        if (dx > -1){
            dy = 0;
            dx -= ACCELERATION;
        }
        break;
    default:
        break;
    }
}
World::~World(){
    for (vector<Block*> v : mStreets)
        for (Block * b : v)
            delete b;
}
