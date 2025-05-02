#include "archer.hpp"

ArcherTower :: ArcherTower(int xpos, int ypos, int damage, int speed, int scope, int regTime, int reloadTime, int type, int towerVision) : Tower (xpos, ypos, damage, speed, scope, regTime, reloadTime, type, towerVision) {}

void ArcherTower :: Upgrade1() {
    int actDamage =  this->getDamage(); 
    actDamage += 10;
    this->setDamage(actDamage);
}

void ArcherTower :: Upgrade2() {
    int actDamage =  this->getDamage(); 
    actDamage += 10;
    this->setDamage(actDamage);
}

void ArcherTower :: Upgrade3() {
    int actDamage =  this->getDamage(); 
    actDamage += 10;
    this->setDamage(actDamage);
}