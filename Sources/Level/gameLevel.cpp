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
                case '*': // Front kin tower
                    row.push_back(3);
                    break;
                case 'G': // Goal
                    row.push_back(4);
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

    RenderMapTexture(map);
    
    return map;
}

void RenderMapTexture(Map& map) {
    InitTextures(); // Initialize all Textures -> gameTextures.hpp

    // Load map for render texture
    map.renderTexture = LoadRenderTexture(map.width * CELL_SIZE, map.height * CELL_SIZE);

    // Render map for texture
    BeginTextureMode(map.renderTexture);
        ClearBackground(BLANK);  // Clear with transparent background

        // Iterates in the Map Matrix
        for (int y = 0; y < map.height; y++) {
            for (int x = 0; x < map.width; x++) {
                Rectangle cell = {(float)x * CELL_SIZE, (float)y * CELL_SIZE, 
                    (float)CELL_SIZE, (float)CELL_SIZE};

                // Case to Render the respective Texture
                switch (map.grid[y][x]) {
                    case 0: // Ground
                        DrawTexturePro(GameTextures::ground, { float(RandomUtils::randomInt(3,4)) * CELL_SIZE, 0, CELL_SIZE, CELL_SIZE }, 
                            cell, {0.0f, 0.0f}, 0.0f, WHITE);
                        break;
                    
                    case 1: // Solid Ground
                        DrawTexturePro(GameTextures::grass, { float(RandomUtils::randomInt(1,3) * CELL_SIZE), CELL_SIZE, CELL_SIZE, CELL_SIZE }, 
                            cell, {0.0f, 0.0f}, 0.0f, WHITE);

                        // 50% chance for a Tree
                        if (RandomUtils::checkProbability(0.5)) {
                            DrawTexturePro(GameTextures::tree, { 
                                float(RandomUtils::randomInt(0,3) * CELL_SIZE), 0, CELL_SIZE, CELL_SIZE }, 
                                cell, {0.0f, 0.0f}, 0.0f, WHITE);
                        }

                        // 5% chance for a Cabin (independent of tree)
                        if (RandomUtils::checkProbability(0.05)) {
                            DrawTexturePro(GameTextures::cabin, { float(RandomUtils::randomInt(0,2) * CELL_SIZE),
                                float(RandomUtils::randomInt(0,3) * CELL_SIZE),
                                CELL_SIZE, CELL_SIZE }, 
                                cell, {0.0f, 0.0f}, 0.0f, WHITE);
                        }
                        break;

                    case 2: // Shore
                        DrawTexturePro(GameTextures::shore, { float(RandomUtils::randomInt(2, 4) * CELL_SIZE), 
                            0, CELL_SIZE, CELL_SIZE }, cell, {0.0f, 0.0f}, 0.0f, WHITE);
                        
                        // 1% chance for a Boat
                        if (RandomUtils::checkProbability(0.01)) {
                            DrawTexturePro(GameTextures::boat, { float(RandomUtils::randomInt(1,2) * CELL_SIZE), 0,
                                CELL_SIZE, CELL_SIZE }, 
                                cell, {0.0f, 0.0f}, 0.0f, WHITE);
                        }
                        break;
                    
                    case 3: // Kin Tower
                        DrawTexturePro(GameTextures::kinTower, { CELL_SIZE, CELL_SIZE * 5, CELL_SIZE, CELL_SIZE }, 
                            cell, {0.0f, 0.0f}, 0.0f, WHITE);
                        break;
                        
                    default:
                        break;
                }

                Rectangle keepCell = {
                    (float)map.goal.x * CELL_SIZE - CELL_SIZE/2, 
                    (float)map.goal.y * CELL_SIZE - CELL_SIZE/2,
                    CELL_SIZE * 2, 
                    CELL_SIZE * 2
                };
                DrawTexturePro(GameTextures::keep, 
                    {0, 0, CELL_SIZE * 2, CELL_SIZE * 2}, 
                    keepCell, {0.0f, 0.0f}, 0.0f, WHITE);
            }
        }
    EndTextureMode();
    map.textureInitialized = true;
}

void DrawMap(const Map& map){
    if (!map.textureInitialized) return;
    
    // Draw texture
    DrawTextureRec(
        map.renderTexture.texture,
        (Rectangle){0, 0, (float)map.renderTexture.texture.width, -(float)map.renderTexture.texture.height},
        (Vector2){0, 0},
        WHITE
    );
}

void DrawTower(const Map& map, int x, int y, int type, int visionTower) {
    if (type == 1) {
        DrawArcher(x,y, visionTower);
    } 

    if (type == 2) {
        DrawWizard(x,y, visionTower);
    } 

    if (type == 3) {
        DrawArtillery(x,y, visionTower);
    } 
}

void DrawArcher(int x, int y, int visionTower) {

    Rectangle cell = {(float)x * CELL_SIZE, (float)y * CELL_SIZE, 
        (float)CELL_SIZE, (float)CELL_SIZE}; // Respective Cell

    DrawTexturePro(GameTextures::grass, { float(RandomUtils::randomInt(1,3) * CELL_SIZE), CELL_SIZE, CELL_SIZE, CELL_SIZE }, 
        cell, {0.0f, 0.0f}, 0.0f, WHITE);

    DrawTexturePro(GameTextures::archerTowerBase, { 0,5, CELL_SIZE, CELL_SIZE }, 
        cell, {0.0f, 0.0f}, 0.0f, WHITE);
    
    if (visionTower == 1) {
        DrawTexturePro(GameTextures::archerForTower, { 353, 16, CELL_SIZE, CELL_SIZE }, 
            cell, {0.0f, 0.0f}, 0.0f, WHITE);
    }
    if (visionTower == 2) {
        DrawTexturePro(GameTextures::archerForTower, { 353, 33, CELL_SIZE, CELL_SIZE }, 
            cell, {0.0f, 0.0f}, 0.0f, WHITE);
    }
    if (visionTower == 3) {
        DrawTexturePro(GameTextures::archerForTower, { 353, 66, CELL_SIZE, CELL_SIZE }, 
            cell, {0.0f, 0.0f}, 0.0f, WHITE);
    }
    if (visionTower == 4) {
        DrawTexturePro(GameTextures::archerForTower, { 353, 50, CELL_SIZE, CELL_SIZE }, 
            cell, {0.0f, 0.0f}, 0.0f, WHITE);
    }

}

void DrawWizard(int x, int y, int visionTower){

    Rectangle cell = {(float)x * CELL_SIZE, (float)y * CELL_SIZE, 
        (float)CELL_SIZE, (float)CELL_SIZE}; // Respective Cell

    DrawTexturePro(GameTextures::grass, { float(RandomUtils::randomInt(1,3) * CELL_SIZE), CELL_SIZE, CELL_SIZE, CELL_SIZE }, 
        cell, {0.0f, 0.0f}, 0.0f, WHITE);
        

    DrawTexturePro(GameTextures::wizardTowerBase, { 0,8, CELL_SIZE, CELL_SIZE }, 
        cell, {0.0f, 0.0f}, 0.0f, WHITE);

    if (visionTower == 1) {
        DrawTexturePro(GameTextures::wizardForTower, { 352, 207, CELL_SIZE, CELL_SIZE }, 
            cell, {0.0f, 0.0f}, 0.0f, WHITE);
    }

    if (visionTower == 2) {
        DrawTexturePro(GameTextures::wizardForTower, { 352, 161, CELL_SIZE, CELL_SIZE }, 
            cell, {0.0f, 0.0f}, 0.0f, WHITE);
    }

    if (visionTower == 3) {
        DrawTexturePro(GameTextures::wizardForTower, { 352, 193, CELL_SIZE, CELL_SIZE }, 
            cell, {0.0f, 0.0f}, 0.0f, WHITE);
    }

    if (visionTower == 4) {
        DrawTexturePro(GameTextures::wizardForTower, { 352, 176, CELL_SIZE, CELL_SIZE }, 
            cell, {0.0f, 0.0f}, 0.0f, WHITE);
    }

}

void DrawArtillery(int x, int y, int visionTower) {
    Rectangle cell = {(float)x * CELL_SIZE, (float)y * CELL_SIZE, 
        (float)CELL_SIZE, (float)CELL_SIZE}; // Respective Cell

    DrawTexturePro(GameTextures::grass, { float(RandomUtils::randomInt(1,3) * CELL_SIZE), CELL_SIZE, CELL_SIZE, CELL_SIZE }, 
        cell, {0.0f, 0.0f}, 0.0f, WHITE);
        
    
    if (visionTower == 1) {
        DrawTexturePro(GameTextures::artilleryTowerBase, { 240,192, CELL_SIZE, CELL_SIZE }, 
            cell, {0.0f, 0.0f}, 0.0f, WHITE);
    }

    if (visionTower == 2) {
        DrawTexturePro(GameTextures::artilleryTowerBase, { 239,224, CELL_SIZE, CELL_SIZE }, 
            cell, {0.0f, 0.0f}, 0.0f, WHITE);
    }

    if (visionTower == 3) {
        DrawTexturePro(GameTextures::artilleryTowerBase, { 240,208, CELL_SIZE, CELL_SIZE }, 
            cell, {0.0f, 0.0f}, 0.0f, WHITE);
    }

    if (visionTower == 4) {
        DrawTexturePro(GameTextures::artilleryTowerBase, { 242,240, CELL_SIZE, CELL_SIZE }, 
            cell, {0.0f, 0.0f}, 0.0f, WHITE);
    }

}