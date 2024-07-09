#include "Floor.h"
#include "Character.h"

Floor::Floor(string texture, int row, int column) : Tile(texture, row, column)
{
    texture = isFloor;
}


// leave always true
bool Floor::onLeave(Tile *destTile, Character *who)
{
    if(destTile->getTexture() == isWall || destTile->getTexture()==closedDoor || who->getIsDead() || character->getIsDead()){
        return false;
    }
    return true;
}

pair<bool, Tile *> Floor::onEnter(Character *who)
{
    bool result = true;
    if(hasCharacter()){
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
