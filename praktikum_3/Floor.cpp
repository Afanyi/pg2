#include "Floor.h"
#include "Character.h"

Floor::Floor(string texture, int row, int column) : Tile(texture, row, column)
{
    texture = isFloor;
}

bool Floor::moveTo(Tile *destTile, Character *who)
{

    Tile* formalTile = who->getTile(); // obtaining formal tile
    formalTile->setCharacter(nullptr);
    destTile->setCharacter(who); // setting new tile to character
    who->setTile(destTile); // setting character to new tile
    return true;
}

// leave always true
bool Floor::onLeave(Tile *destTile, Character *who)
{
    if(destTile->getTexture() == isWall || destTile->getTexture()==closedDoor){
        return false;
    }
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
