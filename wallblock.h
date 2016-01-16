#ifndef WALLBLOCK_H
#define WALLBLOCK_H
#include "block.h"

class WallBlock : public Block
{
public:
    WallBlock();


    // Block interface
public:
    double maxSpeed();
    bool isSolid();
private:
    const double MAXSPEED = 0;

    // Block interface
public:
    void draw();
};

#endif // WALLBLOCK_H
