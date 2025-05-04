/** 
 *  @file Sources/Enemies/gameEnemies.hpp
 *  @brief defines the Enemy class for enemy entities management 
 */

#ifndef ENEMY_H
#define ENEMY_H

#include <vector>
#include <utility>
#include "raylib.h"

/**
 * @enum EnemyType
 * @brief Types of enemies with distinct attributes
 * 
 * @var EnemyType::Orc
 * @brief resistance [archers], weakness [magic, artillery], speed [slow]  
 * @var EnemyType::DarkMage
 * @brief resistance [magic], weakness [archers, artillery], speed [fast] 
 * @var EnemyType::Minotaur
 * @brief attackBy [magic, archers], speed [medium-slow] 
 * @var EnemyType::Assassin
 * @brief resistance [archers, artillery], weakness [magic], speed [medium-fast] 
 */

enum class EnemyType {
    Orc,
    DarkMage,
    Minotaur,
    Assassin
};

/**
 * @class Enemy
 * @brief represents an enemy entity with grid-based movement along a predefined pathway
 * 
 * @param gridPosition : (x, y) grid based position of the object
 * @param size : (width, height) in pixels
 * @param speed : movement multiplier (recommended : speed > 30)
 * @param pathway : sequence of grid positions defining the movement path
 * @param step : current index in pathway
 * @param setProgress : progress (0.0 to 1.0) between current and next step
 */

class Enemy {
private:
    // === Attributes ===
    
    // position & coordinates
    Vector2 gridPosition; 

    // rendering attributes
    Vector2 size;
    Color color;

    // stats
    EnemyType type;
    int health;
    float speed;
    
    // movement mechanics
    std::vector<Vector2> pathway;
    size_t step = 0;
    float stepProgress = 0.0f;

public:
    Enemy(Vector2 position_ = Vector2(), 
          Vector2 size_ = Vector2(), 
          Color color_ = Color(),
          EnemyType type_ = EnemyType::Orc, 
          float speed_ = 1.0f
          );

   // === Getters ===
    EnemyType getType() const;
    int getHealth() const;
    Vector2 getGridPosition() const;
    Vector2 getWorldPosition() const;
    Vector2 getSize() const;
    float getSpeed() const;
    std::vector<Vector2> getPathway() const;
    size_t getStep() const;
    float getStepProgress() const;

    // === Setters ===
    void setHealth(int newHealth);
    void setGridPosition(const Vector2& pos);
    void setWorldPosition(const Vector2& pos);
    void setSize(const Vector2& newSize);
    void setColor(const Color& newColor);
    void setSpeed(float newSpeed);
    void setPathway(const std::vector<Vector2>& newPathway);
    void setStep(const size_t newStep);
    void setStepProgress(const float newStepProgress);
};

#endif // ENEMY_H
