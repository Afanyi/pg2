#ifndef PIT_H
#define PIT_H
#include "Floor.h"

class Pit : public Floor{
public:
    Pit(string texture, int row, int column);
    string getTexture() override;
    bool moveTo(Tile* destTile, Character* who) override;
    bool onLeave(Tile* destTile, Character* who) override;
    pair<bool, Tile*> onEnter(Character* who) override;
};
#endif // PIT_H
