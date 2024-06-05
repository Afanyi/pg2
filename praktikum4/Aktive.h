#ifndef AKTIVE_H
#define AKTIVE_H
#include "Passive.h"
#include <vector>

using std::vector;

class Active{
public:
    vector<Passive*> passiveObjects;
public:
    virtual void attach(Passive*);
    virtual void detach(Passive*);
    virtual void activate();
};
#endif // AKTIVE_H
