#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include "AbstractUI.h"

enum class Direction{front,back,left, right,still};

enum class CharacterTyp{mainPlayer,Player,NPC};

using std::string;
class Tile;
class Level;
//class AbstractUI;
class Character{
    bool isDead = false;
    bool isLootchestFound = false;
    string typ;
    Tile* tile;
    Level* currentLevel = nullptr;
    Direction direction;
    int Strength;
    int Stamina;
    int Hitpoints;
    CharacterTyp charTyp;

    AbstractController* terminal;

public:
    Input move();
    int getMaxHP();
    Character(const string &typ, CharacterTyp charTyp,int strength=5, int stigma=5);
    ~Character();
    string getTyp() const;
    void setTile(Tile *newTile);
    //friend void move();
    Tile *getTile() const;
    AbstractController *getTerminal() const;
    void setTerminal(AbstractController *newTerminal);
    Direction getDirection() const;
    void setDirection(Direction newDirection);
    Direction getLastDirection() const;
    void setLastDirection(Direction newLastDirection);
    int getStrength() const;
    void setStrength(int newStrength);
    int getStamina() const;
    void setStamina(int newStamina);
    int getHitpoints() const;
    void setHitpoints(int newHitpoints);
    Level *getCurrentLevel() const;
    void setCurrentLevel(Level *newCurrentLevel);
    CharacterTyp getCharTyp() const;
    bool getIsLootchestFound() const;
    void setIsLootchestFound(bool newIsLootchestFound);
    bool getIsDead() const;
    void setIsDead(bool newIsDead);
};

#endif // CHARACTER_H

