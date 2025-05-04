#include "gameLevel.hpp"

Map LoadMapFromSaves(const char* fileName) {
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
        row.reserve(line.size());
        for (size_t x = 0; x < line.size(); x++) {
            char c = line[x];
            switch (c) {
                case ' ': // Default walkable path
                    row.push_back(0);
                    break;
                case '#': // Non-walkable
                    row.push_back(1);
                    break;
                case '$': // Special walkable path
                    row.push_back(2);
                    break;
                case 'S': // Starting position for enemies
                    row.push_back(0);
                    map.start.push_back({ (float)x, (float)y });
                    break;
                case '*': // Special Structure
                    row.push_back(3);
                    break;
                case 'G': // Goal position
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
    
    file.close(); 
    
    if (map.grid.empty()) {
        TraceLog(LOG_ERROR, "Map is empty");
        return map;
    }
    
    map.width = static_cast<int>(map.grid[0].size());
    map.height = static_cast<int>(map.grid.size());

    RenderMapTexture(map);
    return map;
}

void RenderMapTexture(Map& map) {
    // Ensure textures are loaded
    InitTextures();

    // Create render texture matching map dimensions
    map.renderTexture = LoadRenderTexture(
        map.width * CELL_SIZE, map.height * CELL_SIZE);

   // Begin drawing to render texture
    BeginTextureMode(map.renderTexture);
        ClearBackground(BLANK);

       // Render each cell in the map grid
        for (int y = 0; y < map.height; y++) {
            for (int x = 0; x < map.width; x++) {

                // Cell rectangle in pixel coordinates
                Rectangle cell = {
                    static_cast<float>(x) * CELL_SIZE,
                    static_cast<float>(y) * CELL_SIZE,
                    static_cast<float>(CELL_SIZE),
                    static_cast<float>(CELL_SIZE)
                };

                // Render based on cell type
                switch (map.grid[y][x]) {
                    case 0: // Ground/Path
                        DrawTexturePro(
                            GameTextures::ground,
                            { float(RandomUtils::randomInt(3,4)) * CELL_SIZE, 0, CELL_SIZE, CELL_SIZE }, 
                            cell, {0.0f, 0.0f}, 0.0f, WHITE);
                        break;
                    
                    case 1: // Grass/Tree
                        DrawTexturePro(
                            GameTextures::grass,
                            { float(RandomUtils::randomInt(1,3) * CELL_SIZE), CELL_SIZE, CELL_SIZE, CELL_SIZE }, 
                            cell, {0.0f, 0.0f}, 0.0f, WHITE);

                        // 50% chance for a Tree
                        if (RandomUtils::checkProbability(0.5)) {
                            DrawTexturePro(GameTextures::tree, { 
                                float(RandomUtils::randomInt(0,3) * CELL_SIZE), 0, CELL_SIZE, CELL_SIZE }, 
                                cell, {0.0f, 0.0f}, 0.0f, WHITE);
                            break;
                        }

                        // 5% chance for a Cabin (independent of tree)
                        if (RandomUtils::checkProbability(0.05)) {
                            DrawTexturePro(GameTextures::cabin, { float(RandomUtils::randomInt(0,2) * CELL_SIZE),
                                float(RandomUtils::randomInt(0,3) * CELL_SIZE),
                                CELL_SIZE, CELL_SIZE }, 
                                cell, {0.0f, 0.0f}, 0.0f, WHITE);
                            break;
                        }

                        break;

                    case 2: // Shore/River
                        DrawTexturePro(
                            GameTextures::shore,
                            { float(RandomUtils::randomInt(2, 4) * CELL_SIZE), 0, CELL_SIZE, CELL_SIZE },
                            cell, {0.0f, 0.0f}, 0.0f, WHITE);
                        
                        // 1% chance for a Boat
                        if (RandomUtils::checkProbability(0.01)) {
                            DrawTexturePro(GameTextures::boat, { float(RandomUtils::randomInt(1,2) * CELL_SIZE), 0,
                                CELL_SIZE, CELL_SIZE }, 
                                cell, {0.0f, 0.0f}, 0.0f, WHITE);
                        }

                        break;
                    
                    case 3: // Kin Tower
                        DrawTexturePro(
                            GameTextures::kinTower, 
                            { CELL_SIZE, CELL_SIZE * 5, CELL_SIZE, CELL_SIZE }, 
                            cell, {0.0f, 0.0f}, 0.0f, WHITE);

                        break;
                        
                    default:
                        break;
                }

                Rectangle keepRect = {
                    map.goal.x * CELL_SIZE - CELL_SIZE/2, 
                    map.goal.y * CELL_SIZE - CELL_SIZE/2,
                    CELL_SIZE * 2, 
                    CELL_SIZE * 2
                };
                DrawTexturePro(
                    GameTextures::keep,
                    {0, 0, CELL_SIZE * 2, CELL_SIZE * 2},
                    keepRect,
                    {0.0f, 0.0f},
                    0.0f,
                    WHITE
                );
            }
        }
    EndTextureMode();
    map.textureInitialized = true;
}

void DrawMap(const Map& map){
    if (!map.textureInitialized) return;
    
    DrawTextureRec(
        map.renderTexture.texture,
        (Rectangle){0, 0, (float)map.renderTexture.texture.width, -(float)map.renderTexture.texture.height},
        (Vector2){0, 0},
        WHITE);
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