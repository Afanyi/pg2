#include "Aktive.h"

void Active::attach(Passive * p)
{
    p->setId(passiveObjects.size());
    passiveObjects.push_back(p);
}

void Active::detach(Passive *p)
{
    int pos = 0;
    for(auto passive : passiveObjects){
        if(passive->getId() == p->getId()){
            break;
        }
        pos++;
    }
    passiveObjects.erase(passiveObjects.begin()+pos);
}

void Active::activate()
{
    for(auto pasive : passiveObjects){
        pasive->notify();
    }
}

