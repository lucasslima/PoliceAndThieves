#ifndef HIDEOUTBLOCK_H
#define HIDEOUTBLOCK_H
#include "block.h"

class HideoutBlock : public Block
{
public:
    HideoutBlock();

    // Block interface
public:
    void draw();
};

#endif // HIDEOUTBLOCK_H
