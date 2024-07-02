#include "Aktive.h"


void Active::attach(Passive * p)
{
    // only one passive maximum
    for(auto passive : passiveObjects){
        if(p == passive){
            return;
        }
    }
    p->setId(passiveObjects.size());
    passiveObjects.push_back(p);
    p->setActive(this);
    //p->actives.push_back(this);
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
        pasive->notify(this);
    }
}

Active::~Active()
{
    for(auto p : passiveObjects){
        delete p;
    }
}

