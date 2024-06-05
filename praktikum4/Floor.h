#ifndef FLOOR_H
#define FLOOR_H
#include "Tile.h"

class Floor : public Tile{
    //const string isFloor = ".";
public:
    Floor(string texture, int row, int column);
    //bool moveTo(Tile* destTile, Character* who) override;
    bool onLeave(Tile* destTile, Character* who) override;
    pair<bool, Tile*> onEnter(Character* who) override;
    string getTexture() override;
};
#endif // FLOOR_H
