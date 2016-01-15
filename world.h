#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include "block.h"

using std::vector;
class World
{
public:
    World();
    void loadStreets();
    void update();
    void render();

private:
    vector<vector<Block> > mStreets;
};

#endif // WORLD_H
