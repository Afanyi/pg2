#include "Floor.h"
#include "Character.h"
#include <iostream>

Floor::Floor(string texture, int row, int column) : Tile(texture, row, column)
{
    texture = isFloor;
}


// leave always true
bool Floor::onLeave(Tile *destTile, Character *who)
{
    std::cout << "onleave called " << std::endl;
    if(destTile->getTexture() == isWall || destTile->getTexture()==closedDoor ){
        std::cout << "onleave false " << std::endl;
        return false;
    }
    std::cout << "onleave false " << std::endl;
    return true;
}

pair<bool, Tile *> Floor::onEnter(Character *who)
{
    bool result = true;
    if(hasCharacter()){
        std::cout << "floor init " << std::endl;
        Character* defendingChar = getCharacter();
        if(defendingChar != nullptr && who!= nullptr){
            if(defendingChar->getCharTyp() == who->getCharTyp()){
                result = false;
            }
            else{
                defendingChar->setHitpoints(defendingChar->getHitpoints() - who->getStrength());
                if(defendingChar->getHitpoints() <= 0){
                    defendingChar->setIsDead(true);
                    setCharacter(nullptr);
                    // delete defendingChar;
                    result = true;
                }
                else{
                    who->setHitpoints(who->getHitpoints() - defendingChar->getStamina());
                    if(who->getHitpoints() <= 0){
                        who->setIsDead(true);
                        Tile* whoTile = who->getTile();
                        whoTile->setCharacter(nullptr);
                        // delete who;
                    }
                    result = false;
                }
            }
        }
    }
    pair<bool,Tile* > a;
    a.first = result;
    a.second = nullptr;
    return a;
}

string Floor::getTexture()
{

    return isFloor;
}
