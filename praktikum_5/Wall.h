#ifndef WALL_H
#define WALL_H
#include "Tile.h"

class Wall : public Tile{
    //const string isWall = "#";
public:
    Wall(string texture, int row, int column);
    bool moveTo(Tile* destTile, Character* who) override;
    bool onLeave(Tile* destTile, Character* who) override;
    pair<bool, Tile*> onEnter(Character* who) override;
    string getTexture() override;
};
#endif // WALL_H
