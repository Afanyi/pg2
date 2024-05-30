#ifndef ABSTRACTUI_H
#define ABSTRACTUI_H
#include "Level.h"

enum class Input{up,down,left,right,exxit};
class AbstractUI{
public:
    virtual void draw(Level*)=0;
    virtual Input move()=0;
};

class TerminalUI : public AbstractUI{
public:
    TerminalUI();
    void draw(Level* l) override;
    Input move() override;
    Input ConvertNumberToInput(int input);
};
#endif // ABSTRACTUI_H
