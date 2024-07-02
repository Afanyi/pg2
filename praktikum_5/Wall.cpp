#include "Wall.h"
#include "Character.h"

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
    return false;
}
