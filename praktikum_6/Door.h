#ifndef DOOR_H
#define DOOR_H
#include "Floor.h"
#include "Passive.h"

class Door : public Passive, public Floor{
    bool isOpened;
public:
    Door(string texture, int row, int column);
    //~Door() ;
    string getTexture() override;
    void notify(Active* active) override;
    bool getIsOpened() const;
    void setIsOpened(bool newIsOpened);
    bool onLeave(Tile* destTile, Character* who) override;
    pair<bool, Tile*> onEnter(Character* who) override;

};
#endif // DOOR_H
