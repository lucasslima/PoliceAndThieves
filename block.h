#ifndef BLOCK_H
#define BLOCK_H
#include "drawutils.h"

using DrawUtils::Point;

class Block
{
public:
    Block(double maxSpeed, bool isSolid);
    virtual void draw()=0;
    virtual ~Block();
    double getMAXSPEED() const;
    void setCoordinates(int x, int y);
    Point getCoordinates() const;
    bool isSolid() const;
    const double BOCK_SIZE = 10;
protected:
    const double MAXSPEED;
    const bool IS_SOLID;
    Point coordinates;
};

#endif // BLOCK_H
