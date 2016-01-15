#include "world.h"
#include <string>
#include <fstream>
#include "highspeedblock.h"
#include "lowspeedblock.h"
#include "hideoutblock.h"
#include "wallblock.h"

using std::string;
using std::ifstream;
World::World() {}

void World::loadStreets(string pathToMap) {
  ifstream mapFile(pathToMap);
  if (mapFile.is_open()) {
    string line;
    while (getline(mapFile, line)) {
        mStreets.push_back(vector<Block*>());
        for (char c : line){
            switch (c){
            case ' ':
                mStreets.back().push_back(new HighSpeedBlock());
                break;
            case '%':
                mStreets.back().push_back(new WallBlock());
                break;
            case 'b':
                mStreets.back().push_back(new LowSpeedBlock());
                break;
            case '#':
                mStreets.back().push_back(new HideoutBlock());
                break;

            }
        }
    }
  }
}
