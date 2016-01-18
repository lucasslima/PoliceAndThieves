#include "lowspeedblock.h"

LowSpeedBlock::LowSpeedBlock():Block(8.33333,false)
{

}

void LowSpeedBlock::draw(){
    std::vector<Point> blockDrawPoints;
    blockDrawPoints.push_back(Point(coordinates.getX(),coordinates.getY()+BLOCK_SIZE));
    blockDrawPoints.push_back(Point(coordinates.getX() + BLOCK_SIZE, coordinates.getY() + BLOCK_SIZE));
    blockDrawPoints.push_back(Point(coordinates.getX() + BLOCK_SIZE,coordinates.getY()));
    blockDrawPoints.push_back(coordinates);
    glColor3d(0.0,0.5,0.0);
    DrawUtils::drawPoligon(blockDrawPoints);
}


