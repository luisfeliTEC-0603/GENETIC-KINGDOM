#include "tower.hpp"
#include "math.h"
#include "../Textures/gameTextures.hpp"
Tower::Tower (int xpos, int ypos, int damage, int speed, int scope, int regTime, int reloadTime, int type, int towerID)
    : xpos(xpos), ypos(ypos), damage(damage), speed(speed), scope(scope),
      regTime(regTime), reloadTime(reloadTime), type(type) {}

void Tower::Upgrade1() {}
void Tower::Upgrade2() {}
void Tower::Upgrade3() {}

void Tower::ShootEnemy(Enemy& enemy, vector<Bullet>& bulletList) {


  Vector2 towerPos = {
    (float)xpos * CELL_SIZE + CELL_SIZE / 2,
    (float)ypos * CELL_SIZE + CELL_SIZE / 2
  };

  Vector2 enemyPos = enemy.position;

  Vector2 dir = {enemyPos.x + CELL_SIZE / 2 - towerPos.x, enemyPos.y + CELL_SIZE / 2 - towerPos.y}; //  + CELL_SIZE / 2  so it aims the center

  float length = sqrt(dir.x * dir.x + dir.y * dir.y);
  dir.x /= length;
  dir.y /= length;

  bulletList.push_back(Bullet(towerPos, dir, this->speed, damage, this->towerID, &enemy)); // Bullet id is the same as the tower so when it si deleted is easy to detect which tower decrease bullet count
  activeBullets++; // adds new bullet
}


void Tower::CheckIfEnemyesInRange(vector<Enemy>& enemies, vector<Bullet>& bulletList, float deltaTime) {

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

  for (Enemy& e : enemies) {
      if (e.position.x  >= (xpos - scope) * CELL_SIZE && e.position.x <= (xpos + scope) * CELL_SIZE &&
          e.position.y >= (ypos - scope) * CELL_SIZE && e.position.y <= (ypos + scope) * CELL_SIZE) {
          
          ShootEnemy(e, bulletList);
          timeSinceLastShot = 0.0f; // reset
          break; // shoot only once
      }
  }
}
