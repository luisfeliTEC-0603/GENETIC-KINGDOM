#include "gameEnemies.hpp"

Enemy::Enemy(Vector2 position_, 
            Vector2 size_, 
            EnemyType type_
            )
    : gridPosition(position_), size(size_), type(type_) {

        switch(type_) {
            case EnemyType::Orc:
                health = 30;
                speed = 10.0f;
                resistances = {1};
                break;
            case EnemyType::DarkMage:
                health = 20;
                speed = 15.0f;
                resistances = {1, 3};
                break;
            case EnemyType::Undead:
                health = 40;
                speed = 15.0f;
                resistances = {0};
                break;
            case EnemyType::Assassin:
                health = 15;
                speed = 25.0f;
                resistances = {2};
                break;
        }
    }

EnemyType Enemy::getType() { return type; }
int Enemy::getHealth() const { return health; }
Vector2 Enemy::getGridPosition() const { return gridPosition; }
Vector2 Enemy::getWorldPosition() const {
    return { gridPosition.x * size.x, gridPosition.y * size.y };
}
Vector2 Enemy::getSize() const { return size; }
EnemyDirection Enemy::getDirection() const { return dir; }
float Enemy::getSpeed() const { return speed; }
std::vector<Vector2> Enemy::getPathway() const { return pathway; }
size_t Enemy::getStep() const { return step; }
float Enemy::getStepProgress() const { return stepProgress; }
int Enemy::getWalkFrame() const { return walkFrame; }
std::vector<int> Enemy::getResistances() const { return resistances; }

void Enemy::setHealth(int newHealth) { health = newHealth; }
void Enemy::setGridPosition(const Vector2& pos) { gridPosition = pos; }
void Enemy::setWorldPosition(const Vector2& pos) { gridPosition = { pos.x / size.x, pos.y / size.y }; }
void Enemy::setSize(const Vector2& newSize) { size = newSize; }
void Enemy::setDirection(EnemyDirection newDir) { dir = newDir; }
void Enemy::setSpeed(float newSpeed) { speed = newSpeed; }
void Enemy::setPathway(const std::vector<Vector2>& newPathway) { pathway = newPathway; }
void Enemy::setStep(const size_t newStep) { step = newStep; }
void Enemy::setStepProgress(const float newStepProgress) { stepProgress = newStepProgress; }
void Enemy::setWalkFrame(const int newStep) { walkFrame = newStep; }
