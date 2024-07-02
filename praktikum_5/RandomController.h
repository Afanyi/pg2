#ifndef RANDOMCONTROLLER_H
#define RANDOMCONTROLLER_H
#include "AbstractUI.h"

class RandomController : public AbstractController{
public:
    Input move() override;
};
#endif // RANDOMCONTROLLER_H
