#ifndef WHIZARD_H
#define WHIZARD_H

#include "tower.h"

class WhizardTower : public Tower {
public:
    WhizardTower (int xpos, int ypos, int damage, int speed, int scope, int regTime, int reloadTime, int type, string imageDir);
    void Upgrade1 () override;
    void Upgrade2 () override;
    void Upgrade3 () override;
};

#endif