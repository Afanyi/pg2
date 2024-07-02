#include "Ramp.h"

Ramp::Ramp(string texture, int row, int column) : Floor(texture,row,column)
{

}

string Ramp::getTexture()
{
    // if(character == nullptr)
    //     return isRamp;
    // else {
    //     return CharacterPresent;
    // }
    return isRamp;
}
