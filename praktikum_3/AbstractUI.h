#ifndef ABSTRACTUI_H
#define ABSTRACTUI_H
#include "Level.h"

enum class Input{up,down,left,right,exxit};
class AbstractUI{
public:
    virtual void draw(Level*)=0;
    virtual Input move()=0;
};

class AbstractView{
public:
    virtual void draw(Level*)=0;
};

class AbstractController{
public:
    virtual Input move()=0;
};


#endif // ABSTRACTUI_H
