#include "artillery.hpp"

ArtilleryTower :: ArtilleryTower(int xpos, int ypos, int damage, int speed, int scope, int regTime, int reloadTime, int type, int towerVision) : Tower (xpos, ypos, damage, speed, scope, regTime, reloadTime, type, towerVision) {}

void ArtilleryTower :: Upgrade1() {
    int actDamage =  this->getDamage(); 
    actDamage += 10;
    increaseSpecialAttack(10); 
    this->setDamage(actDamage);
}

void ArtilleryTower :: Upgrade2() {
    int actDamage =  this->getDamage(); 
    actDamage += 10;
    increaseSpecialAttack(10); 
    this->setDamage(actDamage);
}

void ArtilleryTower :: Upgrade3() {
    int actDamage =  this->getDamage(); 
    actDamage += 10;
    increaseSpecialAttack(5); 
    this->setDamage(actDamage);
}