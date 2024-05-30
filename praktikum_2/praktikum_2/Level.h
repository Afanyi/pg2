#ifndef LEVEL_H
#define LEVEL_H
#include <vector>
#include "Tile.h"
//#include "Character.h"
using std::vector;

class Character;
class Level{
    vector<vector<Tile*>> tiles;
    vector<Character*> characters;
    int width;
    int height;
public:
    Level();
    ~Level();
    Tile *getTile(int row, int col);
    vector<Portal* > portals;
    //const Tile *getTile(int row, int col);
    void placeCharacter(Character *c, int row, int col);
    void printLevel();
    vector<vector<Tile *> > getTiles() const;
    void setPortalSettings();
};

#endif // LEVEL_H
