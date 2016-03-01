#include "wallblock.h"

using DrawUtils::Point;

WallBlock::WallBlock():Block(0,true)
{

}

void WallBlock::draw()
{
    glPushMatrix();
        glColor3d(0.0,0.0,1.0);
        DrawUtils::drawCube(BLOCK_SIZE, coordinates);
    glPopMatrix();
}
