#ifndef ENEMY_H
#define ENEMY_H

#include <vector>
#include <utility>
#include "raylib.h"

class Enemy {
private:
    Vector2 position;
    Vector2 size;
    Color color;
    float speed;
   // std::vector<std::pair<int, int>> pathway;

public:
    Enemy(Vector2 position_ = Vector2(), 
          Vector2 size_ = Vector2(), 
          Color color_ = Color(), 
          float speed_ = 1.0f
          // std::vector<std::pair<int, int>> pathway_ = {}
          );

    // Getters
    Vector2 getPosition() const;
    Vector2 getSize() const;
    float getSpeed() const;
    // std::vector<std::pair<int, int>> getPathway() const;

    // Setters
    void setPosition(const Vector2& newPosition);
    void setSize(const Vector2& newSize);
    void setColor(const Color& newColor);
    void setSpeed(float newSpeed);
    // void setPathway(const std::vector<std::pair<int, int>>& newPathway);
};

#endif // ENEMY_H
