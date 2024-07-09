#ifndef ATTACKCONTROLLER_H
#define ATTACKCONTROLLER_H
#include "AbstractUI.h"
#include "Level.h"
#include "Character.h"

class AttackController: public AbstractController{
private:
    Level* level;
    Character* character;
    Character* zombie;
public:
    AttackController(Level *level,Character* character,Character* zombie);
    Input move() override;

    Level *getLevel() const;
    void setLevel(Level *newLevel);
    Character *getCharacter() const;
    void setCharacter(Character *newCharacter);
    Character *getZombie() const;
    void setZombie(Character *newZombie);
};
#endif // ATTACKCONTROLLER_H
