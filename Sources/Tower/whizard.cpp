#include "whizard.hpp"

WhizardTower :: WhizardTower(int xpos, int ypos, int damage, int speed, int scope, int regTime, int reloadTime, int type, int towerVision) : Tower (xpos, ypos, damage, speed, scope, regTime, reloadTime, type, towerVision) {}

void WhizardTower :: Upgrade1() {
    int actDamage =  this->getDamage(); 
    actDamage += 10;
    this->setDamage(actDamage);
}

void WhizardTower :: Upgrade2() {
    int actDamage =  this->getDamage(); 
    actDamage += 10;
    this->setDamage(actDamage);
}

void WhizardTower :: Upgrade3() {
    int actDamage =  this->getDamage(); 
    actDamage += 10;
    this->setDamage(actDamage);
}