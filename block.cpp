#include "block.h"

const double Block::BLOCK_SIZE = 10;

Block::Block(double maxSpeed,bool isSolid):MAXSPEED(maxSpeed),IS_SOLID(isSolid) {

}

double Block::getMAXSPEED() const
{
    return MAXSPEED;
}

//x and y must correspond to the center of the block
void Block::setCoordinates(double x, double y, double z)
{
    coordinates = Point(x, y, z);
}

DrawUtils::Point Block::getCoordinates() const
{
    return coordinates;
}

bool Block::isSolid() const
{
    return IS_SOLID;
}



std::vector<Direction>& Block::getCanTurnDirections()
{
    return mCanTurnDirections;
}


Block::~Block(){

}
