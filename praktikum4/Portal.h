#ifndef PORTAL_H
#define PORTAL_H
#include "Tile.h"

class Portal : public Tile{
    //const string isPortal = "o";
    Portal* destination;
public:
    Portal(string texture, int row, int column);
    //bool moveTo(Tile* destTile, Character* who) override;
    bool onLeave(Tile* destTile, Character* who) override;
    pair<bool, Tile*> onEnter(Character* who) override;
    string getTexture() override;
    Portal *getDestination() const;
    void setDestination(Portal *newDestination);
};
#endif // PORTAL_H
