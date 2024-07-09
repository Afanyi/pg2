#include "Passive.h"
#include "Aktive.h"

Active *Passive::getActive() const
{
    return active;
}

void Passive::setActive(Active *newActive)
{
    active = newActive;
}

int Passive::getId() const
{
    return id;
}

void Passive::setId(int newId)
{
    id = newId;
}

