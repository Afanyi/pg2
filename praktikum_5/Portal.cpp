#include "Portal.h"
#include "Character.h"

Portal *Portal::getDestination() const
{
    return destination;
}

void Portal::setDestination(Portal *newDestination)
{
    destination = newDestination;
}

int Portal::getId() const
{
    return id;
}

void Portal::setId(int newId)
{
    id = newId;
}

Portal::Portal(string texture, int row, int column) : Tile(texture, row, column),destination(nullptr)
{
    texture = isPortal;
}


bool Portal::onLeave(Tile *destTile, Character *who)
{
    if(destTile->getTexture() == isWall || destTile->getTexture()==closedDoor){
        return false;
    }
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
    // if(character == nullptr)
    //     return isPortal;
    // else {
    //     return CharacterPresent;
    // }
    return isPortal;
}
