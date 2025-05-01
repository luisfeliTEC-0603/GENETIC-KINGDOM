#include "gameLevel.hpp"

#include <fstream>
#include <string>

#include "../Textures/gameTextures.hpp"

Map LoadMapFromSaves(const char* fileName) {
    Map map; // Map -> gameLevel.hpp
    std::ifstream file(fileName); // Open file in the current directory
    
    if (!file.is_open()) { // Check if the file was open successfully
        TraceLog(LOG_ERROR, "Failed to open map file");
        return map;
    }

    std::string line; // Each row in the file is an array of char
    int y = 0; // Column in the file
    
    while (std::getline(file, line)) { // While the file is still readable-line not empty

        std::vector<int> row; // Row of numbers to include in the map-vector

        for (size_t x = 0; x < line.size(); x++) { // Iterates for each char in line
            
            char c = line[x]; // Respective char

            switch (c) {

                // Enemy-Walkable path -> 0
                case ' ':
                    row.push_back(0);
                    break;

                case '#': // Wall
                    row.push_back(1);
                    break;
                case '$':
                    row.push_back(2);
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
                    row.push_back(1);
                    break;
            }
        }
        map.grid.push_back(row);
        y++;
    }
    
    file.close(); // Close file
    
    if (map.grid.empty()) { // Checks map was read
        TraceLog(LOG_ERROR, "Map is empty");
        return map;
    }
    
    // Get map dimensions
    map.height = map.grid.size();
    map.width = map.grid[0].size();
    
    return map;
}

void DrawMap(const Map& map) { // Renders Map
    
    InitTextures(); // Initialize all Textures -> gameTextures.hpp

    // Iterates in the Map Matrix
    for (int y = 0; y < map.height; y++) {
        for (int x = 0; x < map.width; x++) {

            Rectangle cell = {(float)x * CELL_SIZE, (float)y * CELL_SIZE, 
                (float)CELL_SIZE, (float)CELL_SIZE}; // Respective Cell
            
            // Case to Render the respective Texture
            switch (map.grid[y][x]){

            case 0:
                DrawTexturePro(GameTextures::ground, { 16, 0, CELL_SIZE, CELL_SIZE }, 
                    cell, {0.0f, 0.0f}, 0.0f, WHITE);
                break;
            
            case 1:
                DrawRectangleRec(cell, WALL_COLOR);
                break;
            
            default:
                break;
            }

            // Draw the Keep
            if (x == (int)map.goal.x && y == (int)map.goal.y) {
                DrawRectangleRec(cell, GOAL_COLOR);
            }
        }
    }
}

void DrawTower(const Map& map, int x, int y, int type) {
    if (type == 1) {
        DrawArcher(x,y);
    } 

    if (type == 2) {
        DrawWizard(x,y);
    } 

    if (type == 3) {
        DrawArtillery(x,y);
    } 
}

void DrawArcher(int x, int y) {

    Rectangle cell = {(float)x * CELL_SIZE, (float)y * CELL_SIZE, 
        (float)CELL_SIZE, (float)CELL_SIZE}; // Respective Cell

    DrawTexturePro(GameTextures::archerTowerBase, { 0,5, CELL_SIZE, CELL_SIZE }, 
        cell, {0.0f, 0.0f}, 0.0f, WHITE);

    DrawTexturePro(GameTextures::archerForTower, { 353, 50, CELL_SIZE, CELL_SIZE }, 
        cell, {0.0f, 0.0f}, 0.0f, WHITE);
}

void DrawWizard(int x, int y){

    Rectangle cell = {(float)x * CELL_SIZE, (float)y * CELL_SIZE, 
        (float)CELL_SIZE, (float)CELL_SIZE}; // Respective Cell

    DrawTexturePro(GameTextures::whizardTowerBase, { 0,8, CELL_SIZE, CELL_SIZE }, 
        cell, {0.0f, 0.0f}, 0.0f, WHITE);

    DrawTexturePro(GameTextures::whizardForTower, { 352, 193, CELL_SIZE, CELL_SIZE }, 
        cell, {0.0f, 0.0f}, 0.0f, WHITE);
}

void DrawArtillery(int x, int y) {
    Rectangle cell = {(float)x * CELL_SIZE, (float)y * CELL_SIZE, 
        (float)CELL_SIZE, (float)CELL_SIZE}; // Respective Cell

    DrawTexturePro(GameTextures::artilleryTowerBase, { 240,192, CELL_SIZE, CELL_SIZE }, 
        cell, {0.0f, 0.0f}, 0.0f, WHITE);
}