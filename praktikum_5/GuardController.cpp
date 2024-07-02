#include "GuardController.h"
#include <iostream>

void GuardController::setGuardSring(const std::string &newGuardSring)
{
    guardSring = newGuardSring;
}

Input GuardController::move()
{
    Input result;
    if(guardSring[i] == '2'){
        result =  Input::up;
    }
    else if(guardSring[i] == '8'){
        result = Input::down;
    }
    else if(guardSring[i] == '4'){
        result = Input::left;
    }
    else if(guardSring[i] == '6'){
        result = Input::right;
        std::cout << " from controller : " << std::endl;
    }
    else{
        result = Input::still;
    }
    i ++;
    if(i>=guardSring.size()){
        i = 0;
    }

    return result;
}

GuardController::GuardController()
{
    i = 0;
}
