#include "block.h"

Block::Block(double maxSpeed,bool isSolid):MAXSPEED(maxSpeed),IS_SOLID(isSolid) {

}

double Block::getMAXSPEED() const
{
    return MAXSPEED;
}

bool Block::isSolid() const
{
    return IS_SOLID;
}

Block::~Block(){

}
