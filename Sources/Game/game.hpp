#ifndef GAME_HPP
#define GAME_HPP

#include "../Enemies/gameEnemies.hpp"
#include "../Level/gameLevel.hpp"
#include "../Textures/gameTextures.hpp"

void UpdateEnemy(Enemy& enemy, const Map& map);
bool CheckWinCondition(const Enemy& enemy, const Map& map);

#endif