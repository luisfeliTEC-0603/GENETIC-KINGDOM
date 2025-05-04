#include "tower.hpp"
#include "math.h"
#include "../Textures/gameTextures.hpp"
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

  bulletList.push_back(Bullet(towerPos, dir, this->speed, damage, &enemy)); // Bullet id is the same as the tower so when it si deleted is easy to detect which tower decrease bullet count
  activeBullets++; // adds new bullet
}


void Tower::CheckIfEnemyesInRange(vector<Enemy*>& enemies, vector<Bullet>& bulletList, float deltaTime) {

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
          
          // Calcular diferencia en X y Y
          float dx = e->getWorldPosition().x - towerPixelX;
          float dy = e->getWorldPosition().y - towerPixelY;
  
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
  
          ShootEnemy(*e, bulletList);
          timeSinceLastShot = 0.0f;
          break; // disparar solo una vez
      }
  }
  
}
