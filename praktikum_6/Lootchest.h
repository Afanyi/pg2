#ifndef LOOTCHEST_H
#define LOOTCHEST_H
#include "Floor.h"

class Lootchest : public Floor{
public:
    Lootchest(string texture, int row, int column);
    string getTexture() override;
    pair<bool, Tile*> onEnter(Character* who) override;
};
#endif // LOOTCHEST_H
