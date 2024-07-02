#ifndef LEVELCHANGER_H
#define LEVELCHANGER_H
#include "Portal.h"
#include "Aktive.h"

class Levelchanger : public Portal, public Active{
private:
    Levelchanger* destination;
    string texture;
    int levelchangerId;
public:
    Levelchanger(string texture, int row, int column);
    string getTexture() override;
    pair<bool, Tile*> onEnter(Character* who) override;
    vector<Passive*> passiveObjects;
    Levelchanger *getDestination() const;
    void setDestination(Levelchanger *newDestination);
    int getLevelchangerId() const;
    void setLevelchangerId(int newLevelchangerId);
};
#endif // LEVELCHANGER_H
