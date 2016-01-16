#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include <string>
#include "drawutils.h"
#include "block.h"

using std::vector;
using std::string;
using namespace DrawUtils;
class World
{
public:
    World();
    void loadStreets(string pathToMap);
    void initializeRendering();
    void update();
    void render(void);
    ~World();

private:
    vector<vector<Block*> > mStreets;
    Point origin;
    double mWorldWidth;
    double mWorldHeight;
    double mWorldLeft;
    double mWorldRight;
    double mWorldTop;
    double mWorldBottom;
};

#endif // WORLD_H
