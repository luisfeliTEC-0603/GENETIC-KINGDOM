/** 
 *  @file Sources/Game/game.hpp
 *  @brief Core game logic and state management
 */

#ifndef GAME_HPP
#define GAME_HPP

#include "raylib.h"

#include "../Enemies/gameEnemies.hpp"
#include "../Level/gameLevel.hpp"
#include "../UIElements/TowerSelectionScreen/towerSelection.hpp"
#include "../UIElements/TowerUpgradeScreen/TowerUpgradeScreen.hpp"
#include "../Textures/gameTextures.hpp"
#include "../Currency/currency.hpp"
#include "Pathfinding/aStar.hpp"

/**
 * @def newEnemy
 * @param map reference to the current game map
 * @param start start position for the enemy
 * @param type reference to the type of enemy to spawn
 * @return Pointer to the newly created enemy
 */

Enemy* newEnemy(const Map& map, const Vector2& start, EnemyType type);

/**
 * @def DrawPathway
 * @param enemy reference to the enemy whose path to draw
 * @param pathColor Color to use for path visualization
 * 
 * @brief visualizes an enemy's pathway
 */
void DrawPathway(const Enemy& enemy, Color pathColor);

/**
 * @def UpdateEnemy
 * @param enemy pointer to the enemy to update
 * @param deltaTime time since last frame (in seconds)
 * 
 * @brief updates enemy state and position
 */
void UpdateEnemy(Enemy* enemy, const float deltaTime);

/**
 * @def CheckDefeatCondition
 * @param enemy reference to the enemy to check
 * @param map reference to the current game map
 * @return true if enemy has reached the map's goal position
 * 
 * @brief Checks if an enemy has reached the goal
 */
bool CheckDefeatCondition(const Enemy& enemy, const Map& map);

#endif