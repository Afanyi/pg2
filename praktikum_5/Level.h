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
#include "Lootchest.h"
#include "Levelchanger.h"
#include <fstream>
#include <sstream>
#include <string>
//#include "Character.h"
using std::vector;

class Character;
class Level{
    vector<vector<Tile*>> tiles;
    int width;
    int height;
    Door* door;
    Switch* switc;
    Door* getDoorpos();
    Switch* getSwitcpos();
    Character* a;
public:
    string l = getLevelString("level1.txt");

    string l1 = {
        "################"
        "#!.............#"
        "#..............#"
        "#..............#"
        "#..............#"
        "#......###X#####"
        "#O.....#.......#"
        "########..._<..#"
        "#.........___..#"
        "#..............#"
        "#.............!#"
        "#O.....?.......#"
        "################"

    };

    static string getLevelString(const std::string& file_path);
    void getDoors();
    vector<Door*> doors;
    void removeDeadFigurs();
    int getCharSize();
    Character* getMainCharacter();
    void switchPortalsetting();
    Level();
    Level(string levelString, int width, int height);
    Level(const Level& l);
    Level& operator=(const Level& l);
    // bool operator==(const Level& rhs) const;
    ~Level();
    Tile *getTile(int row, int col);
    vector<Portal* > portals;
    vector<Levelchanger* > levelChangers;
    //const Tile *getTile(int row, int col);
    void placeCharacter(Character *c, int row, int col);
    void printLevel();
    vector<vector<Tile *> > getTiles() const;
    void setPortalSettings();
    void generateTile();
    Door *getDoor() const;
    Switch *getSwitc() const;
    int getWidth() const;
    int getHeight() const;
    vector<Character *> getCharacters() const;
    vector<Character *> getCharactersSpecial();
    void getLevelChangers();
    vector<Character*> characters;
    vector<Character*> charactersSpecia;
};

#endif // LEVEL_H
