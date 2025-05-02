#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>
#include "raylib.h"

#include "../Utilities/tools.hpp"

struct Map { // Represents the map
    std::vector<std::vector<int>> grid;
    Vector2 start;
    Vector2 goal;

    // Unitary Dimensions
    int width;
    int height;

    // Map Render
    RenderTexture2D renderTexture;
    bool textureInitialized = false;
};

Map LoadMapFromSaves(const char* fileName);
void RenderMapTexture(Map& map);
void DrawMap(const Map& map);
void DrawTower(const Map& map, int x, int y, int type, int visionTower);
void DrawWizard(int x, int y, int visionTower);
void DrawArcher(int x, int y, int visionTower);
void DrawArtillery(int x, int y, int visionTower);

#endif