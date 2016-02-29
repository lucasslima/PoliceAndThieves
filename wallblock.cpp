#include "wallblock.h"

using DrawUtils::Point;

WallBlock::WallBlock():Block(0,true)
{

}

void WallBlock::draw()
{
    glPushMatrix();
        glColor3d(0.0,0.0,1.0);
        GLfloat mat_ambient[]={1.0, 1.0, 0.0, 1.0};
        GLfloat mat_diffuse[]={0.6, 0.6, 0.0, 1.0};
        GLfloat mat_specular[]={0.4, 0.4, 0.0, 1.0};
        GLfloat mat_shininess={30.0};
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
        DrawUtils::drawCube(BLOCK_SIZE, coordinates);
    glPopMatrix();
}
