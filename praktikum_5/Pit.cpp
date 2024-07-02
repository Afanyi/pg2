#include "Pit.h"
#include "Character.h"
Pit::Pit(string texture, int row, int column) : Floor(texture,row,column)
{

}

std::string Pit::getTexture()
{
    // if(character == nullptr)
    //     return isPit;
    // else {
    //     return CharacterPresent;
    // }
    return isPit;
}


bool Pit::onLeave(Tile *destTile, Character *who)
{
    if(destTile->getTexture() == isPit || destTile->getTexture() == isRamp)
        return true;
    else{
        return false;
    }
}

pair<bool, Tile *> Pit::onEnter(Character *who)
{
    pair<bool,Tile* > a;
    a.first = true;
    a.second = nullptr;
    return a;
}
