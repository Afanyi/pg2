#include <iostream>
#include "Door.h"
#include "Character.h"

bool Door::getIsOpened() const
{
    return isOpened;
}

void Door::setIsOpened(bool newIsOpened)
{
    isOpened = newIsOpened;
}

bool Door::moveTo(Tile *destTile, Character *who)
{
    if(isOpened){
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
    else{
        // acts like a wall
        return false;
    }
}

bool Door::onLeave(Tile *destTile, Character *who)
{
    if(isOpened){
        return true;
    }
    else{
        return false;
    }
}

pair<bool, Tile *> Door::onEnter(Character *who)
{
    pair<bool,Tile* > a;
    a.second = nullptr;
    if(isOpened){
        a.first = true;
    }
    else{
        a.first = false;
    }
    return a;
}

Door::Door(string texture, int row, int column): Floor(texture,row,column)
{
    isOpened = false;
}

std::string Door::getTexture()
{
    if(character == nullptr)
        if(!isOpened)
            return closedDoor;
        else{
            return openedDoor;
        }
    else {
        return CharacterPresent;
    }
}

void Door::notify()
{
    setIsOpened(!isOpened);
    std::cout << " hi" << std::endl;
}
