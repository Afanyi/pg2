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


int Character::getStrength() const
{
    return Strength;
}

void Character::setStrength(int newStrength)
{
    Strength = newStrength;
}

int Character::getStamina() const
{
    return Stamina;
}

void Character::setStamina(int newStamina)
{
    Stamina = newStamina;
}

int Character::getHitpoints() const
{
    return Hitpoints;
}

void Character::setHitpoints(int newHitpoints)
{
    Hitpoints = newHitpoints;
}

Level *Character::getCurrentLevel() const
{
    return currentLevel;
}

void Character::setCurrentLevel(Level *newCurrentLevel)
{
    currentLevel = newCurrentLevel;
}

CharacterTyp Character::getCharTyp() const
{
    return charTyp;
}

bool Character::getIsLootchestFound() const
{
    return isLootchestFound;
}

void Character::setIsLootchestFound(bool newIsLootchestFound)
{
    isLootchestFound = newIsLootchestFound;
}

bool Character::getIsDead() const
{
    return isDead;
}

void Character::setIsDead(bool newIsDead)
{
    isDead = newIsDead;
}

Input Character::move()
{
    Input input;
    input = terminal->move();
    return input;
}

int Character::getMaxHP()
{
    return 20 + (Stamina * 5);
}

Character::Character(const std::string &typ,CharacterTyp charTyp, int strength, int stigma) : typ(typ), tile(nullptr),terminal(nullptr),direction(Direction::front),
    Strength(strength),Stamina(stigma),charTyp(charTyp)
{
    Hitpoints = getMaxHP();
}

Character::~Character()
{
    //delete tile;
    //delete terminal;
}
