#ifndef ABSTRACTUI_H
#define ABSTRACTUI_H
#include "Level.h"

enum class Input{up,upleft,upright,down,downleft,downright,left,right,center,exxit};


class AbstractView{
public:
    virtual void draw(Level*)=0;
};

class AbstractController{
public:
    virtual Input move()=0;
};


#endif // ABSTRACTUI_H
