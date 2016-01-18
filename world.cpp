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
    glColor3d(1.0,0.0,0.0);
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
    for ( auto& v : mStreets){
        for (auto& b: v){
            b->setCoordinates(p.getX(),p.getY());
            for (auto i = p.getX(); i <= p.getX() + Block::BLOCK_SIZE ; i++){
                for (auto j = p.getY(); j <= p.getY() + Block::BLOCK_SIZE ; j++){
                    mCurrentBlock[std::pair<int,int>(i,j)] = b;
                    mSpatialHash[std::pair<int,int>(i/32,j/32)].push_back(b);
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
        }else{
            toMove = mCurrentBlock[std::pair<int,int>(mPolice.getX() + 2.5,mPolice.getY())];
            if (toMove->isSolid()){
                mPolice.setX(oldX);
                mPolice.setY(oldY);
                dx = 0;
                dy = 0;
            } else{
                toMove = mCurrentBlock[std::pair<int,int>(mPolice.getX(),mPolice.getY() + 2.5)];
                if (toMove->isSolid()){
                    mPolice.setX(oldX);
                    mPolice.setY(oldY);
                    dx = 0;
                    dy = 0;
                }
            }
        }
    }
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



void World::handleInput(char c, int x, int y)
{
    switch (c){
    case 'w':
        if ( dy > -MAX_SPEED){
            dx = 0;
            dy -= ACCELERATION;
        }
        break;
    case 's':
        if (dy < MAX_SPEED){
            dx = 0;
            dy += ACCELERATION;
        }
        break;
    case 'd':
        if (dx < MAX_SPEED){
            dx +=ACCELERATION;
            dy = 0;
        }
        break;
    case 'a':
        if (dx > -MAX_SPEED){
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
