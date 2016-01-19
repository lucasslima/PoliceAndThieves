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
                mThief.setOrientation(Direction::EAST);
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
    double oldPoliceX = mPolice.getX();
    double oldPoliceY = mPolice.getY();
    double oldThiefX = mThief.getX();
    double oldThiefY = mThief.getY();

    Block * policeBlock = mCurrentBlock[std::pair<int,int>(oldPoliceX,oldPoliceY)];
    Block * thiefBlock = mCurrentBlock[std::pair<int,int>(mThief.getX(),mThief.getY())];


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
                mPolice.setX(policeBlock->getCoordinates().getX() + 5);
                mPolice.setY(policeBlock->getCoordinates().getY()  + 5);
            }
        }
        if (mPoliceWillTurnCounterClockWise)
            mPolice.changeOrientationClockWise();
    }

    if (mThiefWillTurnClockWise){
        mThief.changeOrientationClockWise();
        for (Direction d : thiefBlock->getCanTurnDirections()){
            if (d == mThief.getOrientation()){
                mThiefWillTurnClockWise = false;
                mThief.setX(thiefBlock->getCoordinates().getX() + 5);
                mThief.setY(thiefBlock->getCoordinates().getY()  + 5);
            }
        }
        if (mThiefWillTurnClockWise)
            mThief.changeOrientationCounterClockWise();
    }
    if (mThiefWillTurnCounterClockWise){
        mThief.changeOrientationCounterClockWise();
        for (Direction d : thiefBlock->getCanTurnDirections()){
            if (d == mThief.getOrientation()){
                mThiefWillTurnCounterClockWise = false;
                mThief.setX(thiefBlock->getCoordinates().getX() + 5);
                mThief.setY(thiefBlock->getCoordinates().getY()  + 5);
            }
        }
        if (mThiefWillTurnCounterClockWise)
            mThief.changeOrientationClockWise();
    }

    if (mThief.getOrientation() == Direction::WEST)
        mThief.setX(oldThiefX - mSpeedThief);
    if (mThief.getOrientation() == Direction::EAST)
        mThief.setX(oldThiefX + mSpeedThief);
    if (mThief.getOrientation() == Direction::NORTH)
        mThief.setY(oldThiefY - mSpeedThief);
    if (mThief.getOrientation() == Direction::SOUTH)
        mThief.setY(oldThiefY + mSpeedThief);

    if (mPolice.getOrientation() == Direction::WEST)
        mPolice.setX(oldPoliceX - mSpeedPolice);
    if (mPolice.getOrientation() == Direction::EAST)
        mPolice.setX(oldPoliceX + mSpeedPolice);
    if (mPolice.getOrientation() == Direction::NORTH)
        mPolice.setY(oldPoliceY - mSpeedPolice);
    if (mPolice.getOrientation() == Direction::SOUTH)
        mPolice.setY(oldPoliceY + mSpeedPolice);

    if (policeBlock == thiefBlock)
        std::cout << "Found thieve! "<< std::endl;
    if (typeid(*thiefBlock) == typeid(HideoutBlock))
        std::cout << "Thief Escaped!" << std::endl;
    if (typeid(*policeBlock) == typeid(LowSpeedBlock) )
        mSpeedPolice = policeBlock->getMAXSPEED();
    if (typeid(*thiefBlock) == typeid(LowSpeedBlock) )
        mSpeedThief = policeBlock->getMAXSPEED();

    checkColision(mPolice,oldPoliceX,oldPoliceY,mSpeedPolice);
    checkColision(mThief,oldThiefX,oldThiefY,mSpeedThief);
    glutPostRedisplay();
}

void World::checkColision(Car& car,double oldX, double oldY, double& speed){
    Block * toMove = mCurrentBlock[std::pair<int,int>(car.getX() -2.5,car.getY() - 2.5)];
    if (toMove->isSolid()){
        car.setX(oldX);
        car.setY(oldY);
        speed = 0;
    }
    else{
        toMove = mCurrentBlock[std::pair<int,int>(car.getX() + 2.5,car.getY() + 2.5)];
        if (toMove->isSolid()){
            car.setX(oldX);
            car.setY(oldY);
            speed = 0;
        }else{
            toMove = mCurrentBlock[std::pair<int,int>(car.getX() + 2.5,car.getY())];
            if (toMove->isSolid()){
                car.setX(oldX);
                car.setY(oldY);
                speed = 0;
            } else{
                toMove = mCurrentBlock[std::pair<int,int>(car.getX(),car.getY() + 2.5)];
                if (toMove->isSolid()){
                    car.setX(oldX);
                    car.setY(oldY);
                    speed = 0;
                }
            }
        }
    }
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
        if ( mSpeedPolice < MAX_SPEED){
            mSpeedPolice += ACCELERATION;
        }
        break;
    case 's':
        if ( mSpeedPolice > 0){
            mSpeedPolice -= ACCELERATION;
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
        if (!mPoliceWillTurnCounterClockWise){
            if (mSpeedPolice < 1)
                mSpeedPolice += ACCELERATION;
            mPoliceWillTurnCounterClockWise = true;
        }
        break;
    default:
        break;
    }
}

void World::handleMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            mMouseX = (double)x;
            mMouseY = (double)y;
        }
    }
    glutPostRedisplay();
}

void World::motion(int x, int y)
{
    int deltaX = (x - (int)mMouseX);
    int deltaY = (y - (int)mMouseY);
    int precision = 100;
    if (abs(deltaX) > abs(deltaY)) {
        if (abs(deltaX) > precision) {
            if (deltaX > 0) {
                if (mThief.getOrientation() == Direction::EAST){
                    if (mSpeedThief < MAX_SPEED)
                        mSpeedThief += ACCELERATION;
                }
                else
                    mThiefWillTurnClockWise = true;
            } else {
                if (mThief.getOrientation() == Direction::WEST){
                    if (mSpeedThief < MAX_SPEED)
                        mSpeedThief += ACCELERATION;
                }
                else
                    mPoliceWillTurnCounterClockWise = true;
            }
            glutPostRedisplay();
        }
    } else {
        if (abs(deltaY) > precision) {
            if (deltaY > 0) {
                mThiefWillTurnCounterClockWise = true;
            } else {
                mThiefWillTurnClockWise = true;
            }
            glutPostRedisplay();
        }
    }
}
World::~World(){
    for (vector<Block*> v : mStreets)
        for (Block * b : v)
            delete b;
}
