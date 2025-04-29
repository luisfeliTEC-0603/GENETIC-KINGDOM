#ifndef TEXTURES_HPP
#define TEXTURES_HPP

#include "raylib.h"

namespace GameTextures // Available Textures
{
    extern Texture2D ground;
    extern Texture2D whizardTowerBase;
    extern Texture2D whizardForTower;
}

// Constant Parameters 
const int CELL_SIZE = 16;
const int PLAYER_SIZE = 12;

const Color WALL_COLOR = DARKGRAY;
const Color PATH_COLOR = RAYWHITE;
const Color PLAYER_COLOR = RED;
const Color GOAL_COLOR = GREEN;

void InitTextures();
void UnloadAllTextures();

#endif