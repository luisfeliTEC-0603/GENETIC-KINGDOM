#include "tower.hpp"
#include "math.h"
#include "../Textures/gameTextures.hpp"

#include <iostream>
#include <random>

Tower::Tower (int xpos, int ypos, int damage, int speed, int scope, int regTime, int reloadTime, int type, int towerVision )
    : xpos(xpos), ypos(ypos), damage(damage), speed(speed), scope(scope),
      regTime(regTime), reloadTime(reloadTime), type(type), towerVision(towerVision) {}

void Tower::Upgrade1() {}
void Tower::Upgrade2() {}
void Tower::Upgrade3() {}

void Tower::ShootEnemy(Enemy& enemy, vector<Bullet>& bulletList) {


  Vector2 towerPos = {
    (float)xpos * CELL_SIZE + CELL_SIZE / 2,
    (float)ypos * CELL_SIZE + CELL_SIZE / 2
  };

  Vector2 enemyPos = enemy.getWorldPosition();

  Vector2 dir = {enemyPos.x + CELL_SIZE / 2 - towerPos.x, enemyPos.y + CELL_SIZE / 2 - towerPos.y}; //  + CELL_SIZE / 2  so it aims the center

  float length = sqrt(dir.x * dir.x + dir.y * dir.y);
  dir.x /= length;
  dir.y /= length;

  int Bulltype = 0;
  if (chance()) { Bulltype += 1;} 

  int finalDamage = damage;
  if (Bulltype == 1) {damage *= 2;} // In case there is a special bullet doubles damage

  bulletList.push_back(Bullet(towerPos, dir, this->speed, Bulltype, finalDamage, &enemy)); // Bullet id is the same as the tower so when it si deleted is easy to detect which tower decrease bullet count
  activeBullets++; // adds new bullet
}

bool Tower::chance() { // This is the logic to shoot the special bullet, if probSpecialAttack = x, there x chance to get the special bullet
    int roll = rand() % 100 + 1; // genera un número entre 1 y 100
    return roll <= probSpecialAttack;
}   

void Tower::CheckIfEnemiesInRange(vector<Enemy*>& enemies, vector<Bullet>& bulletList, float deltaTime, int goalx, int goaly) {
    vector<Enemy*> enemisInRange = {};
    int shortGoalDistanceIndex = -1;
    int actualShortDist = std::numeric_limits<int>::max();
    if (activeBullets >= 2 ) {
        timeSinceLastShot += deltaTime;
        if (timeSinceLastShot >= 1.0f) {
            setActiveBullets(0);       // Reset bullets
            reloadTime = 0.0f;       // Reset reload time
            timeSinceLastShot = 0.0f;
        }
        return; // Dont shoot while reloading
    }

    timeSinceLastShot += deltaTime;

    // Shoot only 1 / speed 
    if (timeSinceLastShot < 1 / speed) return;
    
    // Used to set directions of camera view
    float towerPixelX = xpos * CELL_SIZE + CELL_SIZE / 2;
    float towerPixelY = ypos * CELL_SIZE + CELL_SIZE / 2;
    
    for (Enemy* e : enemies) {
        if (e->getWorldPosition().x >= (xpos - scope) * CELL_SIZE && e->getWorldPosition().x <= (xpos + scope) * CELL_SIZE &&
            e->getWorldPosition().y >= (ypos - scope) * CELL_SIZE && e->getWorldPosition().y <= (ypos + scope) * CELL_SIZE) {
            enemisInRange.push_back(e);
        }
    }

    for (int i = 0; i < static_cast<int>(enemisInRange.size()); i++) {
        int distance = std::abs(enemisInRange[i]->getWorldPosition().x - goalx * CELL_SIZE) +
                       std::abs(enemisInRange[i]->getWorldPosition().y - goaly * CELL_SIZE);
        if (distance < actualShortDist) {
            shortGoalDistanceIndex = i;
            actualShortDist = distance;
        }
    }

    if (shortGoalDistanceIndex == -1) {
        // No enemy found
        return;
    }

    // Calcular diferencia en X y Y
    float dx = enemisInRange[shortGoalDistanceIndex]->getWorldPosition().x - towerPixelX;
    float dy = enemisInRange[shortGoalDistanceIndex]->getWorldPosition().y - towerPixelY;

    // Determinar dirección
    if (std::abs(dx) > std::abs(dy)) {
        if (dx > 0) {
            towerVision = 2; // derecha
        } else {
            towerVision = 4; // izquierda
        }
    } else {
        if (dy > 0) {
            towerVision = 3; // abajo
        } else {
            towerVision = 1; // arriba
        }
    }

    ShootEnemy(*enemisInRange[shortGoalDistanceIndex], bulletList);
    timeSinceLastShot = 0.0f;
    
}

