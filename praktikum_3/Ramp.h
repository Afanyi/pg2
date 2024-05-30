#ifndef RAMP_H
#define RAMP_H
#include "Floor.h"

class Ramp :public Floor{
public:
    Ramp(string texture, int row, int column);
    string getTexture() override;
};

#endif // RAMP_H
