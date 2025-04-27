#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>
#include "raylib.h"

struct Map {
    std::vector<std::vector<int>> grid;
    Vector2 start;
    Vector2 goal;
    int width;
    int height;
};

Map LoadMapFromFile(const char* fileName);
void DrawMap(const Map& map);

#endif