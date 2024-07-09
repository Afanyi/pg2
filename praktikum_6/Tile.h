#ifndef TILE_H
#define TILE_H
#include <string>

using std::string;
using std::pair;
class Character;

class Tile{
protected:
    string texture;
    Character* character;
    int row;
    int column;
public:
    const string npcPresent = "n";
    const string CharacterPresent = "x";
    const string isFloor = ".";
    const string isWall = "#";
    const string isPortal = "o";
    const string isSwitch = "?";
    const string openedDoor = "/";
    const string closedDoor = "X";
    const string isPit = "_";
    const string isRamp = "<";
    const string isLevelChanger = "!";
    const string Islootchest = "$";
    virtual ~Tile();
    Tile(string texture, int row, int column);
    Tile& operator=(const Tile& t);
    virtual string getTexture() = 0;
    virtual bool moveTo(Tile* destTile, Character* who);
    virtual bool onLeave(Tile* destTile, Character* who) = 0;
    virtual pair<bool, Tile*> onEnter(Character* who) = 0;
    bool hasCharacter();
    Character *getCharacter() const;
    void setCharacter(Character *newCharacter);
    int getRow() const;
    int getColumn() const;
};





#endif // TILE_H
