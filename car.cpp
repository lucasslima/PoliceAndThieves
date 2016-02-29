#include "car.h"
#include "block.h"

using DrawUtils::Point;

const double Car::CAR_SIZE = 2.5;

Car::Car()
{
    Point position;
}

Car::Car(Point p):mPosition(p)
{

}
double Car::getX() const
{
    return mPosition.getX();
}

double Car::getY() const
{
    return mPosition.getY();
}

void Car::setX(const double x)
{
    mPosition.setX(x);
}

void Car::setY(const double y)
{
    mPosition.setY(y);
}

Point Car::getPosition() const
{
    return mPosition;
}

void Car::setPosition(const Point &position)
{
    mPosition = position;
}

void Car::draw()
{

    glColor3d(1.0,0.0,0.0);
    DrawUtils::drawCube(CAR_SIZE, mPosition);
}

int Car::getOrientation() const
{
    return mOrientation;
}

void Car::setOrientation(Direction d)
{
    mOrientation = d;
}

void Car::changeOrientationCounterClockWise()
{
    if (mOrientation == Direction::NORTH)
        mOrientation = Direction::WEST;
    else
        mOrientation--;
}

void Car::changeOrientationClockWise()
{
    if (mOrientation == Direction::WEST)
        mOrientation = Direction::NORTH;
    else
        mOrientation++;
}

bool checkColision(Block * b){
    return false;
}
