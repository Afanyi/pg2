#ifndef STATIONARYCONTROLLER_H
#define STATIONARYCONTROLLER_H
#include "AbstractUI.h"

class StationaryController: public AbstractController{
public:
    Input move() override;
};
#endif // STATIONARYCONTROLLER_H
