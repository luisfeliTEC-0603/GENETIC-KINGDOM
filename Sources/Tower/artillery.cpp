#include "artillery.hpp"

ArtilleryTower :: ArtilleryTower(int xpos, int ypos, int damage, int speed, int scope, int regTime, int reloadTime, int type, int towerID) : Tower (xpos, ypos, damage, speed, scope, regTime, reloadTime, type, towerID) {}

void ArtilleryTower :: Upgrade1() {
    int actDamage =  this->getDamage(); 
    actDamage += 10;
    this->setDamage(actDamage);
}

void ArtilleryTower :: Upgrade2() {
    int actDamage =  this->getDamage(); 
    actDamage += 10;
    this->setDamage(actDamage);
}

void ArtilleryTower :: Upgrade3() {
    int actDamage =  this->getDamage(); 
    actDamage += 10;
    this->setDamage(actDamage);
}