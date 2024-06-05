#ifndef PASSIVE_H
#define PASSIVE_H

class Passive{
protected:
    int id;
public:
    virtual void notify() = 0;
    int getId() const;
    void setId(int newId);
};
#endif // PASSIVE_H
