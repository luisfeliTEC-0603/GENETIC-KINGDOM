#ifndef ARCHER_H
#define ARCHER_H

#include "tower.hpp"

class ArcherTower : public Tower {
    public:
        ArcherTower (int xpos, int ypos, int damage, int speed, int scope, int regTime, int reloadTime, int type, int towerVision);
        void Upgrade1 () override;
        void Upgrade2 () override;
        void Upgrade3 () override;
    };
    
#endif