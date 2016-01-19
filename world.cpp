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

}

World::World() {
    mPoliceWillTurnClockWise = false;
    mPoliceWillTurnCounterClockWise = false;
}

void World::initializeRendering()
{
    mSpeedPolice = 0;
    mSpeedThief = 0;
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
    for ( int i = 0 ; i < mStreets.size(); i++ ){
        for ( int j = 0 ; j < mStreets[i].size(); j++ ){
            Block* b = mStreets[i][j];
            b->setCoordinates(p.getX(),p.getY());
            if ( i > 0 && !mStreets[i-1][j]->isSolid())
                b->getCanTurnDirections().push_back(Direction::NORTH);
            if (j > 0 && !mStreets[i][j-1]->isSolid())
                b->getCanTurnDirections().push_back(Direction::WEST);
            if (i < mStreets.size() - 1 && !mStreets[i+1][j]->isSolid())
                b->getCanTurnDirections().push_back(Direction::SOUTH);
            if (j < mStreets[i].size() - 1 && !mStreets[i][j+1]->isSolid())
                b->getCanTurnDirections().push_back(Direction::EAST);
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
                mThief.setPosition(b->getCoordinates()) ;
                mThief.setX(mThief.getX() + Car::CAR_SIZE);
                mThief.setY(mThief.getY() + Car::CAR_SIZE);
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
                mPolice.setPosition( mStreets[i][j]->getCoordinates() );
                mPolice.setX(mPolice.getX() + Car::CAR_SIZE);
                mPolice.setY(mPolice.getY() + Car::CAR_SIZE);
                mPolice.setOrientation(Direction::WEST);
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
          //quadrado(mPolice);
          //quadrado(mThieve);
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

    Block * policeBlock = mCurrentBlock[std::pair<int,int>(oldX,oldY)];
    Block * thieveBlock = mCurrentBlock[std::pair<int,int>(mThief.getX(),mThief.getY())];

    if (mPoliceWillTurnClockWise){
        mPolice.changeOrientationClockWise();
        for (Direction d : policeBlock->getCanTurnDirections()){
            if (d == mPolice.getOrientation()){
                mPoliceWillTurnClockWise = false;
                mPolice.setX(policeBlock->getCoordinates().getX() + 5);
                mPolice.setY(policeBlock->getCoordinates().getY()  + 5);
            }
        }
        if (mPoliceWillTurnClockWise)
            mPolice.changeOrientationCounterClockWise();
    }
    if (mPoliceWillTurnCounterClockWise){
        mPolice.changeOrientationCounterClockWise();
        for (Direction d : policeBlock->getCanTurnDirections()){
            if (d == mPolice.getOrientation()){
                mPoliceWillTurnCounterClockWise = false;
            }
            else
                mPolice.changeOrientationClockWise();
        }
    }
    if (mPolice.getOrientation() == Direction::WEST)
        mPolice.setX(oldX - mSpeedPolice);
    if (mPolice.getOrientation() == Direction::EAST)
        mPolice.setX(oldX + mSpeedPolice);
    if (mPolice.getOrientation() == Direction::NORTH)
        mPolice.setY(oldY - mSpeedPolice);
    if (mPolice.getOrientation() == Direction::SOUTH)
        mPolice.setY(oldY + mSpeedPolice);
    if (policeBlock == thieveBlock)
        std::cout << "Found thieve! "<< std::endl;
    if (typeid(*policeBlock) == typeid(HideoutBlock))
        std::cout << "Police stoped on hideout" << std::endl;

    Block * toMove = mCurrentBlock[std::pair<int,int>(mPolice.getX() -2.5,mPolice.getY() - 2.5)];
    if (toMove->isSolid()){
        mPolice.setX(oldX);
        mPolice.setY(oldY);
        mSpeedPolice = 0;
        mSpeedThief = 0;
    }
    else{
        toMove = mCurrentBlock[std::pair<int,int>(mPolice.getX() + 2.5,mPolice.getY() + 2.5)];
        if (toMove->isSolid()){
            mPolice.setX(oldX);
            mPolice.setY(oldY);
            mSpeedPolice = 0;
            mSpeedThief = 0;
        }else{
            toMove = mCurrentBlock[std::pair<int,int>(mPolice.getX() + 2.5,mPolice.getY())];
            if (toMove->isSolid()){
                mPolice.setX(oldX);
                mPolice.setY(oldY);
                mSpeedPolice = 0;
                mSpeedThief = 0;
            } else{
                toMove = mCurrentBlock[std::pair<int,int>(mPolice.getX(),mPolice.getY() + 2.5)];
                if (toMove->isSolid()){
                    mPolice.setX(oldX);
                    mPolice.setY(oldY);
                    mSpeedPolice = 0;
                    mSpeedThief = 0;
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
    mPolice.draw();
    mThief.draw();
    glFlush();
    glutSwapBuffers();
}



void World::handleInput(char c, int x, int y)
{
    switch (c){
    case 'w':
        if ( mSpeedThief < MAX_SPEED){
            mSpeedPolice += ACCELERATION;
        }
        break;
    case 'd':
        if (!mPoliceWillTurnClockWise){
            if (mSpeedPolice < 1)
                mSpeedPolice += ACCELERATION;
            mPoliceWillTurnClockWise = true;
        }
        break;
    case 'a':
        mPolice.changeOrientationCounterClockWise();
        if (mSpeedPolice > -MAX_SPEED){
            mSpeedThief = 0;
            mSpeedPolice -= ACCELERATION;
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
