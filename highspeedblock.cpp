#include "highspeedblock.h"

HighSpeedBlock::HighSpeedBlock():Block(22.2222,false)
{

}

void HighSpeedBlock::draw(){

    glPushMatrix();
        glTranslated(0,0,-BLOCK_SIZE);
        glColor3d(0,0,0);
        DrawUtils::drawCube(BLOCK_SIZE, coordinates);
    glPopMatrix();
}

