#ifndef BLOCK_H
#define BLOCK_H
#include "drawutils.h"
#include <vector>

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
    Block *getNorthNeighbor() const;
    void setNorthNeighbor(Block *northNeighbor);

    Block *getSouthNeighbor() const;
    void setSouthNeighbor(Block *southNeighbor);

    Block *getWestNeightbor() const;
    void setWestNeightbor(Block *westNeightbor);

    Block *getEastNeightbor() const;

    void setEastNeightbor(Block *eastNeightbor);

protected:
    Block* mNorthNeighbor;
    Block* mSouthNeighbor;
    Block* mWestNeightbor;
    Block* mEastNeightbor;
    const double MAXSPEED;
    const bool IS_SOLID;
    Point coordinates;
};

#endif // BLOCK_H
