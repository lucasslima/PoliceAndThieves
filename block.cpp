#include "block.h"

const double Block::BLOCK_SIZE = 10;

Block::Block(double maxSpeed,bool isSolid):MAXSPEED(maxSpeed),IS_SOLID(isSolid) {

}

double Block::getMAXSPEED() const
{
    return MAXSPEED;
}

//x and y must correspond to the center of the block
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

Block *Block::getNorthNeighbor() const
{
    return mNorthNeighbor;
}

void Block::setNorthNeighbor(Block *northNeighbor)
{
    mNorthNeighbor = northNeighbor;
}

Block *Block::getSouthNeighbor() const
{
    return mSouthNeighbor;
}

void Block::setSouthNeighbor(Block *southNeighbor)
{
    mSouthNeighbor = southNeighbor;
}

Block *Block::getWestNeightbor() const
{
    return mWestNeightbor;
}

void Block::setWestNeightbor(Block *westNeightbor)
{
    mWestNeightbor = westNeightbor;
}

Block *Block::getEastNeightbor() const
{
    return mEastNeightbor;
}

void Block::setEastNeightbor(Block *eastNeightbor)
{
    mEastNeightbor = eastNeightbor;
}

Block::~Block(){

}
