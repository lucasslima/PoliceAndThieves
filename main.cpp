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
    world.handleInputKeyboard(c,x,y);
    cout << "Entered key: " << c << endl;
}


void inputMouse(int button, int state,int x, int y){


 //  world.handleInputKeyboard(c,x,y);
   //cout << button << " " <<state<<" " <<x<<" " <<y<<endl;

   world.handleInputMouse(button,  x,  y);


}


void iniciaOpenGL(void)
{
    world.initializeRendering();
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
    glutMouseFunc(inputMouse);
    iniciaOpenGL();
    glutMainLoop();
    return 0;
}
