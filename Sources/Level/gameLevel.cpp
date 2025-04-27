#include "gameLevel.hpp"
#include "../Textures/gameTextures.hpp"
#include <fstream>
#include <string>

Map LoadMapFromFile(const char* fileName) {
    Map map;
    std::ifstream file(fileName);
    
    if (!file.is_open()) {
        TraceLog(LOG_ERROR, "Failed to open map file");
        return map;
    }

    std::string line;
    int y = 0;
    
    while (std::getline(file, line)) {
        std::vector<int> row;
        for (size_t x = 0; x < line.size(); x++) {
            char c = line[x];
            switch (c) {
                case '#': // Wall
                    row.push_back(1);
                    break;
                case ' ': // Path
                    row.push_back(0);
                    break;
                case 'S': // Start
                    row.push_back(0);
                    map.start = {(float)x, (float)y};
                    break;
                case 'G': // Goal
                    row.push_back(0);
                    map.goal = {(float)x, (float)y};
                    break;
                default:
                    row.push_back(1); // Treat unknown characters as walls
                    break;
            }
        }
        map.grid.push_back(row);
        y++;
    }
    
    file.close();
    
    if (map.grid.empty()) {
        TraceLog(LOG_ERROR, "Map is empty");
        return map;
    }
    
    map.height = map.grid.size();
    map.width = map.grid[0].size();
    
    return map;
}

void DrawMap(const Map& map) {
    for (int y = 0; y < map.height; y++) {
        for (int x = 0; x < map.width; x++) {
            Rectangle cell = {(float)x * CELL_SIZE, (float)y * CELL_SIZE, (float)CELL_SIZE, (float)CELL_SIZE};
            
            if (map.grid[y][x] == 1) {
                DrawRectangleRec(cell, WALL_COLOR);
            } else {
                DrawRectangleRec(cell, PATH_COLOR);
                
                // Draw goal position
                if (x == (int)map.goal.x && y == (int)map.goal.y) {
                    DrawRectangleRec(cell, GOAL_COLOR);
                }
            }
        }
    }
}