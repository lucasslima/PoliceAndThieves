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

void quadrado()
{
    glBegin(GL_POLYGON);
        glVertex2dv(vertices[0]);
        glVertex2dv(vertices[1]);
        glVertex2dv(vertices[2]);
        glVertex2dv(vertices[3]);
    glEnd();
}

World::World() {}

void World::initializeRendering()
{
    if (mStreets.size() == 0)
        return;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double worldHeight = mStreets.size() * 10;
    double worldWidth = mStreets[0].size() * 10;
    gluOrtho2D(-worldWidth/2, worldWidth, -worldHeight/2, worldHeight);
    glMatrixMode(GL_MODELVIEW);
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
      mStreets.push_back(vector<Block *>());
      for (char c : line) {
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
    }
    return;
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

    glLoadIdentity();
    glTranslatef(x, y, 0.0);
    glRotatef(teta, 0.0,0.0,1.0);
    glColor3d(1.0,0.0,0.0);
    quadrado();

    glLoadIdentity();
    glTranslatef(x, y, 0.0);
    glRotatef(-teta, 0.0,0.0,1.0);
    glScalef(0.7, 0.7, 0.7);
    glColor3d(0.0,1.0,0.0);
    quadrado();

    glFlush();
    glutSwapBuffers();
}
World::~World(){
    for (vector<Block*> v : mStreets)
        for (Block * b : v)
            delete b;
}
