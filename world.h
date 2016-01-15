#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include <string>

#include "block.h"

using std::vector;
using std::string;

class World
{
public:
    World();
    void loadStreets(string pathToMap);
    void update();
    void render();

private:
    vector<vector<Block*> > mStreets;
};

#endif // WORLD_H
