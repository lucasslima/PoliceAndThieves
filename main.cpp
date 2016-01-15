#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>

using namespace std;

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

float x=0.0, y=0.0,        //centro dos quadrados
      teta=0.0;            //angulo de rotação dos quadrados
float dx=0.01, dy=0.005;   //vetor que define a direcao
                           //inicial de movimento

void exibe(void)
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

 void mover() {
    x += dx; if (x>20 || x<-20) dx*=-1;
    y += dy; if (y>20 || y<-20) dy*=-1;
    teta += 0.1;
    glutPostRedisplay();
}
void teclado(unsigned char c, int xx, int yy) {
    if (c=='q') exit(0);
}

void iniciaOpenGL(void)
{
    /* parâmetros de visualização */
    /* definir janela do mundo no intervalo de
       -20 a 20 (unidades do contexto da aplicação),
       nas direcoes x e y */
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     gluOrtho2D(-20.0, 20.0, -20.0, 20.0);
     glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(700, 700);
    glutCreateWindow("Quadrado");
    glutDisplayFunc(exibe);
    glutIdleFunc(mover);
    glutKeyboardFunc(teclado);
    iniciaOpenGL();
    glutMainLoop();
    return 0;
}
