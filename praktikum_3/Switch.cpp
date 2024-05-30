#include "Switch.h"

Switch::Switch(string texture, int row, int column):Floor(texture,row,column),passiveObjects()
{

}

std::string Switch::getTexture()
{
    if(character == nullptr)
        return isSwitch;
    else {
        return CharacterPresent;
    }
}
