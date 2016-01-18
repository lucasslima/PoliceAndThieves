#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include <string>
#include "drawutils.h"
#include "block.h"
#include <utility>
#include <unordered_map>

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

    void handleInput( char c, int x, int y);
    ~World();

private:
    std::unordered_map< std::pair<int,int>, std::vector<Block*>,DrawUtils::pairhash> mSpatialHash;
    std::unordered_map< std::pair<int,int>, Block*,DrawUtils::pairhash> mCurrentBlock;
    vector<vector<Block*> > mStreets;
    Point origin;
    Point mThieve;
    Point mPolice;
    const float ACCELERATION = 0.3;
    const float MAX_SPEED = 2;
    double dx;
    double dy;
    double mWorldWidth;
    double mWorldHeight;
    double mWorldLeft;
    double mWorldRight;
    double mWorldTop;
    double mWorldBottom;
    bool mPoliceWillTurn, mPoliceWillStop, mThieveWillStop, mThieveWillTurn;
};


#endif // WORLD_H
