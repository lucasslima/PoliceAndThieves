#include "hideoutblock.h"

HideoutBlock::HideoutBlock():Block(0,false)
{

}


void HideoutBlock::draw()
{
    glPushMatrix();
        glColor3d(0.0,1.0,0.0);
        DrawUtils::drawCube(BLOCK_SIZE, coordinates);
    glPopMatrix();
}
