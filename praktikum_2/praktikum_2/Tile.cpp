#include "Tile.h"
#include "Character.h"

Character *Tile::getCharacter() const
{
    return character;
}

void Tile::setCharacter(Character *newCharacter)
{
    character = newCharacter;
}




Floor::Floor(string texture, int row, int column) : Tile(texture, row, column)
{
    texture = isFloor;
}

bool Floor::moveTo(Tile *destTile, Character *who)
{
    // return false if destination is wall
    if(!(onLeave(destTile,who) && onEnter(who).first)){
        return false;
    }

    Tile* formalTile = who->getTile(); // obtaining formal tile
    formalTile->setCharacter(nullptr);
    destTile->setCharacter(who); // setting new tile to character
    who->setTile(destTile); // setting character to new tile
    return true;
}

// leave always true
bool Floor::onLeave(Tile *destTile, Character *who)
{
    return true;
}

pair<bool, Tile *> Floor::onEnter(Character *who)
{
    pair<bool,Tile* > a;
    a.first = true;
    a.second = nullptr;
    return a;
}

string Floor::getTexture()
{
    if(character == nullptr)
        return isFloor;
    else {
        return CharacterPresent;
    }
}





pair<bool, Tile *> Wall::onEnter(Character *who)
{
    pair<bool,Tile* > a;
    a.first = false;
    a.second = nullptr;
    return a;
}

string Wall::getTexture()
{
    if(character == nullptr)
        return isWall;
    else {
        return CharacterPresent;
    }
}

Wall::Wall(string texture, int row, int column) : Tile(texture, row, column)
{
    texture = isWall;
}

bool Wall::moveTo(Tile *destTile, Character *who)
{
    return false;
}

bool Wall::onLeave(Tile *destTile, Character *who)
{
    return true;
}






Portal *Portal::getDestination() const
{
    return destination;
}

void Portal::setDestination(Portal *newDestination)
{
    destination = newDestination;
}

Portal::Portal(string texture, int row, int column) : Tile(texture, row, column),destination(nullptr)
{
    texture = isPortal;
}

bool Portal::moveTo(Tile *destTile, Character *who)
{
    if(!(onLeave(destTile,who) && onEnter(who).first)){
        return false;
    }
    Tile* formalTile = who->getTile();
    formalTile->setCharacter(nullptr);
    destTile->setCharacter(who);
    who->setTile(destTile);
    return true;
}

bool Portal::onLeave(Tile *destTile, Character *who)
{
    return true;
}

pair<bool, Tile *> Portal::onEnter(Character *who)
{
    pair<bool,Tile* > a;
    a.first = true;
    a.second = destination;
    return a;
}

string Portal::getTexture()
{
    if(character == nullptr)
        return isPortal;
    else {
        return CharacterPresent;
    }
}

int Tile::getRow() const
{
    return row;
}

int Tile::getColumn() const
{
    return column;
}

Tile::~Tile()
{

}
// initialising atributes
Tile::Tile(string texture, int row, int column) : texture(texture),
    character(nullptr),
    row(row),
    column(column)
{}
