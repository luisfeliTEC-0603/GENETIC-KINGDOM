/**
 * @file Sources/Textures/gameTextures.hpp
 * @brief texture resource management for game assets
 */

#ifndef TEXTURES_HPP
#define TEXTURES_HPP

#include "raylib.h"

/**
 * @namespace GameTextures
 * @brief contains all loaded game textures as Texture2D objects
 */

namespace GameTextures {
    
    // === Landscape Textures ===
    extern Texture2D ground;
    extern Texture2D keep;
    extern Texture2D tree;
    extern Texture2D cabin;
    extern Texture2D grass;
    extern Texture2D boat;
    extern Texture2D shore;

   // === Tower Textures ===
    extern Texture2D kinTower;
    extern Texture2D wizardTowerBase;
    extern Texture2D wizardForTower;
    extern Texture2D archerForTower;
    extern Texture2D archerTowerBase;
    extern Texture2D artilleryTowerBase;
    
    // === Enemy Textures ===
    extern Texture2D orc;
    extern Texture2D darkMage;
    extern Texture2D undead;
    extern Texture2D assassin;
}

// Constant Parameters 
const int CELL_SIZE = 16;
const int ENEMY_SIZE = 16;

const Color WALL_COLOR = DARKGRAY;
const Color PATH_COLOR = RAYWHITE;
const Color PLAYER_COLOR = RED;
const Color GOAL_COLOR = GREEN;

/**
 * @def InitTextures
 * @brief Loads all game textures into memory
 */

void InitTextures();

/**
 * @def UnloadAllTextures
 * @brief unloads all game textures from memory
 */

void UnloadAllTextures();

#endif