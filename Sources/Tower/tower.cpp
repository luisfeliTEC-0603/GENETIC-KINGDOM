#include "tower.hpp"
#include "math.h"
Tower::Tower (int xpos, int ypos, int damage, int speed, int scope, int regTime, int reloadTime, int type)
    : xpos(xpos), ypos(ypos), damage(damage), speed(speed), scope(scope),
      regTime(regTime), reloadTime(reloadTime), type(type) {}

void Tower::Upgrade1() {}
void Tower::Upgrade2() {}
void Tower::Upgrade3() {}

void Tower:: ShootEnemy(const Enemy& enemy, vector<Bullet>& bulletList) {
  int cellSize = 16;
  Vector2 towerPos = {
    (float)xpos * cellSize + cellSize / 2,
    (float)ypos * cellSize + cellSize / 2
};
  Vector2 enemyPos = enemy.position;

  // Direction vector
  Vector2 dir = {enemyPos.x - towerPos.x, enemyPos.y - towerPos.y};

  float length = sqrt(dir.x * dir.x + dir.y * dir.y);
  dir.x /= length;
  dir.y /= length;

  bulletList.push_back(Bullet(towerPos, dir, 5.0f, damage));
}

void Tower::CheckIfEnemyesInRange(const vector<Enemy>& enemies, vector<Bullet>& bulletList) {
  for (const Enemy& e : enemies) {

    if (e.position.x >= xpos - scope && e.position.x <= xpos + scope &&
        e.position.y >= ypos - scope && e.position.y <= ypos + scope) {
        ShootEnemy(e, bulletList);
    }
  }
}

