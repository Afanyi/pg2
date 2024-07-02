#ifndef PASSIVE_H
#define PASSIVE_H
#include <vector>

using std::vector;
class Active;
class Passive{
protected:
    int id;
    Active* active;
public:
    //vector<Active*> actives;
    virtual void notify(Active* active) = 0;
    int getId() const;
    void setId(int newId);
    Active *getActive() const;
    void setActive(Active *newActive);
};
#endif // PASSIVE_H
