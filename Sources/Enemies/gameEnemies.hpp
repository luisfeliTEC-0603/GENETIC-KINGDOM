#ifndef ENEMY_H
#define ENEMY_H

#include <vector>
#include <utility>
#include "raylib.h"

class Enemy {
private:
    Vector2 gridPosition; 
    Vector2 size;
    Color color;
    float speed;
   std::vector<Vector2> pathway;

public:
    Enemy(Vector2 gridPosition = Vector2(), 
          Vector2 size_ = Vector2(), 
          Color color_ = Color(), 
          float speed_ = 1.0f
          );

    // Getters
    Vector2 getGridPosition() const;
    Vector2 getWorldPosition() const;
    Vector2 getSize() const;
    float getSpeed() const;
    std::vector<Vector2> getPathway() const;

    // Setters
    void setGridPosition(const Vector2& pos);
    void setWorldPosition(const Vector2& pos);
    void setSize(const Vector2& newSize);
    void setColor(const Color& newColor);
    void setSpeed(float newSpeed);
    void setPathway(const std::vector<Vector2>& newPathway);
};

#endif // ENEMY_H
