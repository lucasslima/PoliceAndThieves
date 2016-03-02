
#include "lowspeedblock.h"

LowSpeedBlock::LowSpeedBlock():Block(0.7,false)
{

}

void LowSpeedBlock::draw(){
    glPushMatrix();
        glTranslated(0,0,-BLOCK_SIZE);
        glColor3d(0.0,0.5,0.0);
        DrawUtils::drawCube(BLOCK_SIZE, coordinates);
    glPopMatrix();
}


