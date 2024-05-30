#include "Pit.h"
#include "Character.h"
Pit::Pit(string texture, int row, int column) : Floor(texture,row,column)
{

}

std::string Pit::getTexture()
{
    if(character == nullptr)
        return isPit;
    else {
        return CharacterPresent;
    }
}

bool Pit::moveTo(Tile *destTile, Character *who)
{
    // return false if destination is wall
    // if(!(onLeave(destTile,who) && onEnter(who).first)){
    //     return false;
    // }

    Tile* formalTile = who->getTile(); // obtaining formal tile
    formalTile->setCharacter(nullptr);
    destTile->setCharacter(who); // setting new tile to character
    who->setTile(destTile); // setting character to new tile
    return true;
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
