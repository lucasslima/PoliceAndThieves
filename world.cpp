#include "world.h"
#include <string>
#include <fstream>
#include "highspeedblock.h"
#include "lowspeedblock.h"
#include "hideoutblock.h"
#include "wallblock.h"
#include "GL/gl.h"
#include "GL/glut.h"

using std::string;
using std::ifstream;
static GLdouble vertices[][2] = {{-1.0,-1.0},{1.0,-1.0},
                          {1.0,1.0}, {-1.0,1.0}};

void quadrado(const Point &p)
{
    std::vector<Point> blockDrawPoints;
    blockDrawPoints.push_back(Point(p.getX(),p.getY()-Block::BLOCK_SIZE));
    blockDrawPoints.push_back(Point(p.getX() + Block::BLOCK_SIZE, p.getY() -Block::BLOCK_SIZE));
    blockDrawPoints.push_back(Point(p.getX() + Block::BLOCK_SIZE,p.getY()));
    blockDrawPoints.push_back(p);
    glColor3d(0.0,0.0,0.5);
    DrawUtils::drawPoligon(blockDrawPoints);
}

World::World() {}

void World::initializeRendering()
{
    if (mStreets.size() == 0)
        return;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    mWorldHeight = mStreets.size() * 10;
    mWorldWidth = mStreets[0].size() * 10;
    origin = Point(-mWorldWidth/2,mWorldHeight/2);
    mWorldLeft = -mWorldWidth/2;
    mWorldRight = mWorldWidth/2;
    mWorldBottom = -mWorldHeight/2;
    mWorldTop = mWorldHeight/2;
    gluOrtho2D(mWorldLeft, mWorldRight, mWorldBottom, mWorldTop);
    glMatrixMode(GL_MODELVIEW);
    Point p(origin);
    for ( auto v : mStreets){
        for (Block* b : v){
            b->setCoordinates(p.getX(),p.getY());
            p.setX(p.getX() + Block::BLOCK_SIZE);
        }
        p.setX(origin.getX());
        p.setY(p.getY() - Block::BLOCK_SIZE);
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
                found = true;
                break;
            }
        }
        if (found) break;
    }
    return;
}

float x=0.0, y=0.0,        //centro dos quadrados
      teta=0.0;            //angulo de rotação dos quadrados
float dx=0.01, dy=0.005;   //vetor que define a direcao
                           //inicial de movimento
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
    x += dx; if (x>20 || x<-20) dx*=-1;
    y += dy; if (y>20 || y<-20) dy*=-1;
    teta += 0.1;
    glutPostRedisplay();
}

void World::render(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    quadrado(mPolice);
    Point pen(origin.getX(),origin.getY());
    for (std::vector<Block*> v : mStreets){
        for (Block* b : v){
            b->draw();
            pen.setX(pen.getX() + 10);
            if (b == v.back())
                pen.setX(-165);
        }
        pen.setY(pen.getY() - 10);
    }

    glFlush();
    glutSwapBuffers();
}
World::~World(){
    for (vector<Block*> v : mStreets)
        for (Block * b : v)
            delete b;
}
