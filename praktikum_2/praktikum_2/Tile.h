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
    const string CharacterPresent = "x";
    const string isFloor = ".";
    const string isWall = "#";
    const string isPortal = "o";
    ~Tile();
    Tile(string texture, int row, int column);
    virtual string getTexture() = 0;
    virtual bool moveTo(Tile* destTile, Character* who) = 0;
    virtual bool onLeave(Tile* destTile, Character* who) = 0;
    virtual pair<bool, Tile*> onEnter(Character* who) = 0;
    Character *getCharacter() const;
    void setCharacter(Character *newCharacter);
    int getRow() const;
    int getColumn() const;
};

class Floor : public Tile{
    //const string isFloor = ".";
public:
    Floor(string texture, int row, int column);
    bool moveTo(Tile* destTile, Character* who) override;
    bool onLeave(Tile* destTile, Character* who) override;
    pair<bool, Tile*> onEnter(Character* who) override;
    string getTexture() override;
};

class Wall : public Tile{
    //const string isWall = "#";
public:
    Wall(string texture, int row, int column);
    bool moveTo(Tile* destTile, Character* who) override;
    bool onLeave(Tile* destTile, Character* who) override;
    pair<bool, Tile*> onEnter(Character* who) override;
    string getTexture() override;
};

class Portal : public Tile{
    //const string isPortal = "o";
    Portal* destination;
public:
    Portal(string texture, int row, int column);
    bool moveTo(Tile* destTile, Character* who) override;
    bool onLeave(Tile* destTile, Character* who) override;
    pair<bool, Tile*> onEnter(Character* who) override;
    string getTexture() override;
    Portal *getDestination() const;
    void setDestination(Portal *newDestination);
};
#endif // TILE_H
