#ifndef TEXTURES_HPP
#define TEXTURES_HPP

#include "raylib.h"

namespace GameTextures // Available Textures
{
    extern Texture2D ground;
    extern Texture2D keep;
    extern Texture2D wizardTowerBase;
    extern Texture2D wizardForTower;
    extern Texture2D archerForTower;
    extern Texture2D archerTowerBase;
    extern Texture2D artilleryTowerBase;
    extern Texture2D tree;
    extern Texture2D cabin;
    extern Texture2D grass;
    extern Texture2D boat;
    extern Texture2D shore;
    extern Texture2D kinTower;
}

// Constant Parameters 
const int CELL_SIZE = 16;
const int ENEMY_SIZE = 16;

const Color WALL_COLOR = DARKGRAY;
const Color PATH_COLOR = RAYWHITE;
const Color PLAYER_COLOR = RED;
const Color GOAL_COLOR = GREEN;

void InitTextures();
void UnloadAllTextures();

#endif