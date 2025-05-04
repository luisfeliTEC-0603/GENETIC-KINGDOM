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

Enemy* newEnemy(const Map& map, const Vector2& start);
void DrawPathway(const Enemy& enemy, Color pathColor);
void UpdateEnemy(Enemy& enemy, const Map& map);
bool CheckWinCondition(const Enemy& enemy, const Map& map);

#endif