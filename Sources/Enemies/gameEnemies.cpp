#include "gameEnemies.hpp"

Enemy::Enemy(Vector2 position_, 
             Vector2 size_, 
             Color color_, 
             float speed_,
             std::vector<Vector2> pathway_
             )
    : position(position_), size(size_), color(color_), speed(speed_), pathway(pathway_) {}

Vector2 Enemy::getPosition() const { return position; }
Vector2 Enemy::getSize() const { return size; }
float Enemy::getSpeed() const { return speed; }
std::vector<Vector2> Enemy::getPathway() const { return pathway; }

void Enemy::setPosition(const Vector2& newPosition) { position = newPosition; }
void Enemy::setSize(const Vector2& newSize) { size = newSize; }
void Enemy::setColor(const Color& newColor) { color = newColor; }
void Enemy::setSpeed(float newSpeed) { speed = newSpeed; }
void Enemy::setPathway(const std::vector<Vector2>& newPathway) { pathway = newPathway; }
