#include "Levelchanger.h"

Levelchanger *Levelchanger::getDestination() const
{
    return destination;
}

void Levelchanger::setDestination(Levelchanger *newDestination)
{
    destination = newDestination;
}

int Levelchanger::getLevelchangerId() const
{
    return levelchangerId;
}

void Levelchanger::setLevelchangerId(int newLevelchangerId)
{
    levelchangerId = newLevelchangerId;
}

Levelchanger::Levelchanger(string texture, int row, int column): Portal(texture,row,column)
{
    levelchangerId = 0;
}

string Levelchanger::getTexture()
{
    return isLevelChanger;
}

pair<bool, Tile *> Levelchanger::onEnter(Character *who)
{

    pair<bool,Tile* > a;
    a.first = true;
    activate();
    a.second = destination;
    return a;
}
