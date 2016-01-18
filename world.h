#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include <string>
#include "drawutils.h"
#include "block.h"
#include <utility>
#include <unordered_map>
#include <iostream>

using std::vector;
using std::string;
using namespace DrawUtils;
using namespace std;

class World
{
public:
    World();
    void loadStreets(string pathToMap);
    void initializeRendering();
    void update();
    void render(void);

    void handleInputKeyboard( char c, int x, int y);
    void handleInputMouse( int button, int x, int y);

    ~World();

private:
    std::unordered_map< std::pair<int,int>, std::vector<Block*>,DrawUtils::pairhash> mSpatialHash;
    std::unordered_map< std::pair<int,int>, Block*,DrawUtils::pairhash> mCurrentBlock;
    vector<vector<Block*> > mStreets;
    Point origin;
    Point mThieve;
    Point mPolice;
    const double ACCELERATION = 0.3;
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
