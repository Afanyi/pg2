#include "Lootchest.h"
#include "Character.h"

Lootchest::Lootchest(string texture, int row, int column): Floor(texture,row,column)
{

}

string Lootchest::getTexture()
{
    return Islootchest;
}

pair<bool, Tile *> Lootchest::onEnter(Character *who)
{
    if(who->getCharTyp() != CharacterTyp::NPC){
        who->setIsLootchestFound(true);
    }
    bool result = true;
    pair<bool,Tile* > a;
    a.first = result;
    a.second = nullptr;
    return a;
}
