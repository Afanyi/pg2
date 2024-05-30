#ifndef LEVEL_H
#define LEVEL_H
#include <vector>
#include "Portal.h"
#include "Floor.h"
#include "Wall.h"
#include "Door.h"
#include "Switch.h"
#include "Pit.h"
#include "Ramp.h"
//#include "Character.h"
using std::vector;

class Character;
class Level{
    vector<vector<Tile*>> tiles;
    vector<Character*> characters;
    int width;
    int height;
    Door* door;
    Switch* switc;
    Door* getDoorpos();
    Switch* getSwitcpos();
public:
    const string l = {
        "##########"
        "#O.......#"
        "#...<....#"
        "#..___...#"
        "#..___...#"
        "#........#"
        "#######X##"
        "#O.......#"
        "#...?....#"
        "##########"
    };
    Level();
    Level(const Level& l);
    Level& operator=(const Level& l);
    ~Level();
    Tile *getTile(int row, int col);
    vector<Portal* > portals;
    //const Tile *getTile(int row, int col);
    void placeCharacter(Character *c, int row, int col);
    void printLevel();
    vector<vector<Tile *> > getTiles() const;
    void setPortalSettings();
    void generateTile();
    Door *getDoor() const;
    Switch *getSwitc() const;
};

#endif // LEVEL_H
