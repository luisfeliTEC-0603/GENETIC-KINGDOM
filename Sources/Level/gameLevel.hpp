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
void DrawTower(const Map& map, int x, int y, int type);
void DrawWhizard(int x, int y);
void DrawArcher(int x, int y);
void DrawArtillery(int x, int y);

#endif