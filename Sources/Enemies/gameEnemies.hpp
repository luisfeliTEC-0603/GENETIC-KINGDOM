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
 * @brief types of enemies with distinct attributes
 * 
 * @var EnemyType::Orc
 * @brief resistance [archers], weakness [magic, artillery], speed [slow]  
 * @var EnemyType::DarkMage <-> Mercenaries
 * @brief resistance [archers, artillery], weakness [magic], speed [medium] 
 * @var EnemyType::Undead
 * @brief attackBy [magic, archers], speed [medium] 
 * @var EnemyType::Assassin <-> Dark elf
 * @brief resistance [magic], weakness [archers, artillery], speed [fast] 
 */

enum class EnemyType {
    Orc,
    DarkMage,
    Undead,
    Assassin
};

/**
 * @enum EnemyDirection
 * @brief direction face by he enemy while moving
 * 
 * @var EnemyDirection::down
 * @var EnemyDirection::up
 * @var EnemyDirection::right
 * @var EnemyDirection::left
 * 
 * @note each type number matches with the respective vertical index in its texture 
 */

enum class EnemyDirection {
    down = 0,
    up = 1,
    right = 2,
    left = 3
};

/**
 * @class Enemy
 * @brief represents an enemy entity with grid-based movement along a predefined pathway
 * 
 * @param gridPosition : (x, y) grid based position of the object
 * @param size : (width, height) in pixels
 * @param dir : directio the enemy es facing
 * @param speed : movement multiplier (recommended : speed > 30)
 * @param pathway : sequence of grid positions defining the movement path
 * @param step : current index in pathway
 * @param setProgress : progress (0.0 to 1.0) between current and next step
 * @param walkingStep : index of event in the texture
 * @param resistances : list of int that represent the resistances of each type
 */

class Enemy {
private:
    // === Attributes ===
    
    // position & coordinates
    Vector2 gridPosition; 

    // rendering attributes
    Vector2 size;
    EnemyDirection dir;

    // stats
    EnemyType type;
    int health;
    float speed;
    std::vector<int> resistances = {};
    
    // movement mechanics
    std::vector<Vector2> pathway;
    size_t step = 0;
    float stepProgress = 0.0f;
    int walkFrame = 0;

public:
    Enemy(Vector2 position_ = Vector2(), 
          Vector2 size_ = Vector2(),
          EnemyType type_ = EnemyType::Orc
          );

   // === Getters ===
    EnemyType getType();
    int getHealth() const;
    Vector2 getGridPosition() const;
    Vector2 getWorldPosition() const;
    Vector2 getSize() const;
    EnemyDirection getDirection() const;
    float getSpeed() const;
    std::vector<Vector2> getPathway() const;
    size_t getStep() const;
    float getStepProgress() const;
    int getWalkFrame() const;
    std::vector<int> getResistances() const;

    // === Setters ===
    void setHealth(int newHealth);
    void setGridPosition(const Vector2& pos);
    void setWorldPosition(const Vector2& pos);
    void setSize(const Vector2& newSize);
    void setDirection(EnemyDirection newDir);
    void setSpeed(float newSpeed);
    void setPathway(const std::vector<Vector2>& newPathway);
    void setStep(const size_t newStep);
    void setStepProgress(const float newStepProgress);
    void setWalkFrame(int newStep);
};

#endif // ENEMY_H
