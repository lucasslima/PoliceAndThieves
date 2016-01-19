#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include "world.h"

using namespace std;



static World world;
void render(void)
{
    world.render();
}

void update() {
     world.update();
}
void input(unsigned char c, int x, int y) {
    if (c=='q') exit(0);
    world.handleInput(c,x,y);
    cout << "Entered key: " << c << endl;
}

void mouse(int button, int state, int x, int y) {
    world.handleMouse(button,state,x,y);
}

void iniciaOpenGL(void)
{
    world.initializeRendering();
}
void motion(int x, int y){
    world.motion(x,y);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1600, 900);
    world.loadStreets("map.txt");
    glutCreateWindow("PoliceAndThieves");
    glutDisplayFunc(render);
    glutIdleFunc(update);
    glutKeyboardFunc(input);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    iniciaOpenGL();
    glutMainLoop();
    return 0;
}
