#ifndef CAR_H
#define CAR_H
#include "drawutils.h"

using DrawUtils::Point;

enum Direction{
    NORTH=0,
    EAST,
    SOUTH,
    WEST
};
class Car
{
public:
    Car();
    Car(Point p);
    static const double CAR_SIZE;
    double getX() const;
    double getY() const;
    void setX(const double x);
    void setY(const double y);
    Point getPosition() const;
    void setPosition(const Point &position);
    bool checkColision();
    void draw();
    int getOrientation() const;
    void setOrientation(Direction d);
    void changeOrientationClockWise();
    void changeOrientationCounterClockWise();

private:
    Point mPosition;
    bool isPolice;
    int mOrientation;
};

#endif // CAR_H
