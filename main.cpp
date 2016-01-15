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
void teclado(unsigned char c, int xx, int yy) {
    if (c=='q') exit(0);
}

void iniciaOpenGL(void)
{
    world.initializeRendering();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000, 700);
    world.loadStreets("map.txt");
    glutCreateWindow("PoliceAndThieves");
    glutDisplayFunc(render);
    glutIdleFunc(update);
    glutKeyboardFunc(teclado);
    iniciaOpenGL();
    glutMainLoop();
    return 0;
}
