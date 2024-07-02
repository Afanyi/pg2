#ifndef GUARDCONTROLLER_H
#define GUARDCONTROLLER_H
#include "AbstractUI.h"


class GuardController : public AbstractController{
    unsigned int i = 0;
    std::string guardSring  = "66444466";
public:
    Input move() override;
    GuardController();

    void setGuardSring(const std::string &newGuardSring);
};
#endif // GUARDCONTROLLER_H
