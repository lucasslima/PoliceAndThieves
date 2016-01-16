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
    void setCoordinates(double x, double y);
    Point getCoordinates() const;
    bool isSolid() const;
    static const double BLOCK_SIZE;
protected:
    const double MAXSPEED;
    const bool IS_SOLID;
    Point coordinates;
};

#endif // BLOCK_H
