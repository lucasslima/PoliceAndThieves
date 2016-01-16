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

//    blockDrawPoints.push_back(Point(pen.getX(),pen.getY()-10));
//    blockDrawPoints.push_back(Point(pen.getX()+10,pen.getY()-10));
//    blockDrawPoints.push_back(Point(pen.getX()+10,pen.getY()));
//    blockDrawPoints.push_back(Point(pen) );
}
