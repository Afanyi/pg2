#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include "AbstractUI.h"

using std::string;
class Tile;
//class AbstractUI;
class Character{
    string typ;
    Tile* tile;
    AbstractUI* terminal;

public:
    Input move();
    Character(const string &typ);
    ~Character();
    string getTyp() const;
    void setTile(Tile *newTile);
    friend void move();
    Tile *getTile() const;
    AbstractUI *getTerminal() const;
    void setTerminal(AbstractUI *newTerminal);
};

#endif // CHARACTER_H
