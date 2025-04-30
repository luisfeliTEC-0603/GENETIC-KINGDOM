#include "tower.hpp"

Tower::Tower (int xpos, int ypos, int damage, int speed, int scope, int regTime, int reloadTime, int type)
    : xpos(xpos), ypos(ypos), damage(damage), speed(speed), scope(scope),
      regTime(regTime), reloadTime(reloadTime), type(type) {}

void Tower::Upgrade1() {}
void Tower::Upgrade2() {}
void Tower::Upgrade3() {}
