#include "raylib.h"

#include "Game/game.hpp"

int main() {

    Map gameMap = LoadMapFromFile("Saves/map.txt");
    if (gameMap.grid.empty()) {
        return -1;
    }

    int windowWidth = gameMap.width * CELL_SIZE;
    int windowHeight = gameMap.height * CELL_SIZE;
    
    InitWindow(windowWidth, windowHeight, "CE2103");
    SetTargetFPS(60);

    Enemy player = {
        {(float)gameMap.start.x * CELL_SIZE + (CELL_SIZE - PLAYER_SIZE) / 2, 
         (float)gameMap.start.y * CELL_SIZE + (CELL_SIZE - PLAYER_SIZE) / 2},
        {(float)PLAYER_SIZE, (float)PLAYER_SIZE},
        PLAYER_COLOR
    };

    while (!WindowShouldClose()) {
        UpdateEnemy(player, gameMap);

        if (CheckWinCondition(player, gameMap)) {
            DrawText("You Win!", windowWidth / 2 - 100, windowHeight / 2 - 20, 40, GREEN);
            EndDrawing();
            WaitTime(2);
            break;
        }

        BeginDrawing();
        ClearBackground(BLACK);
        
        DrawMap(gameMap);
        DrawRectangleV(player.position, player.size, player.color);
        
        EndDrawing();
    }

    UnloadAllTextures();
    CloseWindow();
    return 0;
}