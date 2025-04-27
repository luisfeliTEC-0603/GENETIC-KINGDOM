#include "raylib.h"

#include "Game/game.hpp"

int main() {
    // Initialization
    Map gameMap = LoadMapFromFile("Saves/map.txt");
    if (gameMap.grid.empty()) {
        return -1; // Exit if map failed to load
    }

    // Calculate the required window size based on the map dimensions
    int windowWidth = gameMap.width * CELL_SIZE;
    int windowHeight = gameMap.height * CELL_SIZE;
    
    InitWindow(windowWidth, windowHeight, "CE2103");
    SetTargetFPS(60);

    // Create player at the start position
    Enemy player = {
        {(float)gameMap.start.x * CELL_SIZE + (CELL_SIZE - PLAYER_SIZE) / 2, 
         (float)gameMap.start.y * CELL_SIZE + (CELL_SIZE - PLAYER_SIZE) / 2},
        {(float)PLAYER_SIZE, (float)PLAYER_SIZE},
        PLAYER_COLOR
    };

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        UpdateEnemy(player, gameMap);

        // Check win condition
        if (CheckWinCondition(player, gameMap)) {
            DrawText("You Win!", windowWidth / 2 - 100, windowHeight / 2 - 20, 40, GREEN);
            EndDrawing();
            WaitTime(2); // Show win message for 2 seconds
            break;
        }

        // Draw
        BeginDrawing();
        ClearBackground(BLACK);
        
        DrawMap(gameMap);
        DrawRectangleV(player.position, player.size, player.color);
        
        EndDrawing();
    }

    // Cleanup
    CloseWindow();
    return 0;
}