#include "RandomController.h"
#include "time.h"
#include <iostream>
using namespace std;
Input RandomController::move()
{
    int randin;
    srand(time(0));
    Input r;
    randin = rand()%3;
    if(randin == 0){
        r = Input::up;
    }
    else if(randin == 1){
        r = Input::down;
    }
    else if(randin == 2){
        r = Input::left;
    }
    else{
        r = Input::left;
    }
    return r;
}
