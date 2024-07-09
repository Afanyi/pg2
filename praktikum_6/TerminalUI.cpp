#include "TerminalUI.h"
#include <iostream>

TerminalUI::TerminalUI()
{

}

void TerminalUI::draw(Level *l)
{
    l->printLevel();
}

Input TerminalUI::move()
{
    int input;
    Input a;
    std::cout << " enter 1 to move up "
                 "2 to move down 3 : to move left 4 : right any other thing to  exit " << std::endl;
    std::cin >>input;
    if(input == 1){
        a = Input::up;
    }
    else if(input == 2){
        a = Input::down;
    }
    else if(input == 3){
        a = Input::left;
    }
    else if(input == 4){
        a = Input::right;
    }
    else{
        a=Input::up;
    }
    return a;
}

Input TerminalUI::ConvertNumberToInput(int input)
{
    Input a;
    if(input == 1){
        a = Input::up;
    }
    else if(input == 2){
        a = Input::down;
    }
    else if(input == 3){
        a = Input::left;
    }
    else if(input == 4){
        a = Input::right;
    }
    else{
        a=Input::up;
    }
    return a;
}
