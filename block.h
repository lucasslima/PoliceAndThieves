#ifndef BLOCK_H
#define BLOCK_H
#include "drawutils.h"
#include <vector>
#include <car.h>

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

    std::vector<Direction>& getCanTurnDirections();

protected:
    Block* mNorthNeighbor;
    Block* mSouthNeighbor;
    Block* mWestNeightbor;
    Block* mEastNeightbor;
    const double MAXSPEED;
    const bool IS_SOLID;
    Point coordinates;
    std::vector<Direction> mCanTurnDirections;
};

#endif // BLOCK_H
