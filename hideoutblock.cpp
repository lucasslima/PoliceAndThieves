#include "hideoutblock.h"

HideoutBlock::HideoutBlock():Block(0,true)
{

}


void HideoutBlock::draw()
{
    std::vector<Point> blockDrawPoints;
    blockDrawPoints.push_back(Point(coordinates.getX(),coordinates.getY()-BOCK_SIZE));
    blockDrawPoints.push_back(Point(coordinates.getX() + BOCK_SIZE, coordinates.getY() -BOCK_SIZE));
    blockDrawPoints.push_back(Point(coordinates.getX() + BOCK_SIZE,coordinates.getY()));
    blockDrawPoints.push_back(coordinates);
    glColor3d(0.0,1.0,0.0);
    DrawUtils::drawPoligon(blockDrawPoints);
}
