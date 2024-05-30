#ifndef TERMINALUI_H
#define TERMINALUI_H
#include "AbstractUI.h"

class TerminalUI : public AbstractController, public AbstractView{
public:
    TerminalUI();
    void draw(Level* l) override;
    Input move() override;
    Input ConvertNumberToInput(int input);
};
#endif // TERMINALUI_H
