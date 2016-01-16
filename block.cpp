#include "block.h"

const double Block::BOCK_SIZE = 10;

Block::Block(double maxSpeed,bool isSolid):MAXSPEED(maxSpeed),IS_SOLID(isSolid) {

}

double Block::getMAXSPEED() const
{
    return MAXSPEED;
}

void Block::setCoordinates(double x, double y)
{
    coordinates = Point(x,y);
}

DrawUtils::Point Block::getCoordinates() const
{
    return coordinates;
}

bool Block::isSolid() const
{
    return IS_SOLID;
}

Block::~Block(){

}
