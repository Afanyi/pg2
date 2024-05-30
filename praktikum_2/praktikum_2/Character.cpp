#include "Character.h"
#include "Tile.h"

string Character::getTyp() const
{
    return typ;
}

void Character::setTile(Tile *newTile)
{
    tile = newTile;
}

Tile *Character::getTile() const
{
    return tile;
}

AbstractUI *Character::getTerminal() const
{
    return terminal;
}

void Character::setTerminal(AbstractUI *newTerminal)
{
    terminal = newTerminal;
}

Input Character::move()
{
    Input input;
    input = terminal->move();
    return input;
}

Character::Character(const std::string &typ) : typ(typ), tile(nullptr),terminal(nullptr)
{}

Character::~Character()
{
    delete tile;
    delete terminal;
}
