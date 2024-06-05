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

AbstractController *Character::getTerminal() const
{
    return terminal;
}

void Character::setTerminal(AbstractController *newTerminal)
{
    terminal = newTerminal;
}

Direction Character::getDirection() const
{
    return direction;
}

void Character::setDirection(Direction newDirection)
{
    direction = newDirection;
}

Input Character::move()
{
    Input input;
    input = terminal->move();
    return input;
}

Character::Character(const std::string &typ) : typ(typ), tile(nullptr),terminal(nullptr),direction(Direction::front)
{}

Character::~Character()
{
    delete tile;
    delete terminal;
}
