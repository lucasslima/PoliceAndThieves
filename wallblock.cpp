#include "wallblock.h"
#include <vector>
#include "drawutils.h"

using DrawUtils::Point;

WallBlock::WallBlock():Block(0,true)
{

}

void WallBlock::draw()
{
    std::vector<Point> blockDrawPoints;
    blockDrawPoints.push_back(Point(coordinates.getX(),coordinates.getY()-BLOCK_SIZE));
    blockDrawPoints.push_back(Point(coordinates.getX() + BLOCK_SIZE, coordinates.getY() -BLOCK_SIZE));
    blockDrawPoints.push_back(Point(coordinates.getX() + BLOCK_SIZE,coordinates.getY()));
    blockDrawPoints.push_back(coordinates);
    glColor3d(0.0,0.0,1.0);
    DrawUtils::drawPoligon(blockDrawPoints);
}
