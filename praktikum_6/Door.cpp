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
    //if(character == nullptr)
        if(!isOpened)
            return closedDoor;
        else{
            return openedDoor;
         }
    // else {
    //     return CharacterPresent;
    // }
}

void Door::notify(Active* active)
{
    setIsOpened(!isOpened);
    std::cout << " hi" << std::endl;
}
