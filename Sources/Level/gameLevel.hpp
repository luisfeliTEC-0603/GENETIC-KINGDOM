/**
 * @file Sources/Level/gameLevel.hpp
 * @brief Map loading, rendering, and tower drawing functionality
 */

#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>
#include "raylib.h"
#include <fstream>
#include <string>

#include "../Utilities/tools.hpp"
#include "../Textures/gameTextures.hpp"

/**
 * @struct Map
 * @brief Represents the game map with grid data and rendering information
 * 
 * @param grid 2D grid where each cell represents map terrain
 * @param start list of coordinates where enemies spawn
 * @param goal coordinates where enemies aim to reach
 * @param width map dimension in cells
 * @param height map dimension in cells
 * @param renderTexture holds texture of the map 
 * @param textureInitialized flag indicating if renderTexture is ready
 */

struct Map {
    // === grid & data ===
    std::vector<std::vector<int>> grid;
    std::vector<Vector2> start = {};
    Vector2 goal;
    int width;
    int height;

    // === rendering === 
    RenderTexture2D renderTexture;
    bool textureInitialized = false;
};

/**
 * @def LoadMapFromSaves
 * @param fileName path to the map file (.txt)
 * @return Map structure populated with the loaded data
 */

Map LoadMapFromSaves(const char* fileName);

/**
 * @def RenderMapTexture
 * @param map reference to the Map object to render
 * 
 * @brief renders the map to a texture for efficient drawing
 */

void RenderMapTexture(Map& map);

/**
 * @def DrawMap
 * @param map reference to the constant Map object
 * 
 * @brief Uses the pre-rendered texture for optimal performance.
 */

void DrawMap(const Map& map);

// Tower Related
void DrawTower(const Map& map, int x, int y, int type, int visionTower);
void DrawWizard(int x, int y, int visionTower);
void DrawArcher(int x, int y, int visionTower);
void DrawArtillery(int x, int y, int visionTower);

#endif