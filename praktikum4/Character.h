#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include "AbstractUI.h"

enum class Direction{front,back,left, right};

using std::string;
class Tile;
//class AbstractUI;
class Character{
    string typ;
    Tile* tile;
    Direction direction;
    AbstractController* terminal;

public:
    Input move();
    Character(const string &typ);
    ~Character();
    string getTyp() const;
    void setTile(Tile *newTile);
    //friend void move();
    Tile *getTile() const;
    AbstractController *getTerminal() const;
    void setTerminal(AbstractController *newTerminal);
    Direction getDirection() const;
    void setDirection(Direction newDirection);
};

#endif // CHARACTER_H

