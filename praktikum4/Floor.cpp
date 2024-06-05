#include "Floor.h"
#include "Character.h"

Floor::Floor(string texture, int row, int column) : Tile(texture, row, column)
{
    texture = isFloor;
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
    // if(character == nullptr)
    //     return isFloor;
    // else {
    //     return CharacterPresent;
    // }
    return isFloor;
}
