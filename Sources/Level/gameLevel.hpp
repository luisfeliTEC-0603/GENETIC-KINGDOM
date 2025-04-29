#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>
#include "raylib.h"

struct Map { // Represents the map
    std::vector<std::vector<int>> grid;
    Vector2 start;
    Vector2 goal;

    // Unitary Dimensions
    int width;
    int height;
};

Map LoadMapFromSaves(const char* fileName);
void DrawMap(const Map& map);
void DrawWhizardTower (const Map& map);

#endif