#ifndef SWITCH_H
#define SWITCH_H
#include "Aktive.h"
#include "Floor.h"

class Switch : public Active, public Floor{

public:
    vector<Passive*> passiveObjects;
    Switch(string texture, int row, int column);
    string getTexture() override;

};
#endif // SWITCH_H
