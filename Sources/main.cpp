#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"

#include "Game/game.hpp"
#include "System/camera.hpp"

int main() {

    // Initialization
    const int screenWidth = 1280;
    const int screenHeight = 640;
    
    InitWindow(screenWidth, screenHeight, "CE2103");
    SetTargetFPS(60);

    Map gameMap = LoadMapFromFile("Saves/map.txt");
    if (gameMap.grid.empty()) {
        CloseWindow();
        return -1;
    }

    CameraController cameraController;
    cameraController.Initialize(screenWidth, screenHeight, gameMap);

    // Player setup
    Enemy player = {
        {(float)gameMap.start.x * CELL_SIZE + (CELL_SIZE - PLAYER_SIZE) / 2, 
         (float)gameMap.start.y * CELL_SIZE + (CELL_SIZE - PLAYER_SIZE) / 2},
        {(float)PLAYER_SIZE, (float)PLAYER_SIZE},
        PLAYER_COLOR
    };

    // Main game loop
    while (!WindowShouldClose()) {
        // Camera controls
        cameraController.Update(gameMap);

        // Game logic
        UpdateEnemy(player, gameMap);

        // Check win condition
        if (CheckWinCondition(player, gameMap)) {
            BeginDrawing();
                ClearBackground(BLACK);
                DrawText("You Win!", screenWidth/2 - 100, screenHeight/2 - 20, 40, GREEN);
            EndDrawing();
            WaitTime(2);
            break;
        }

        // Drawing
        BeginDrawing();
            ClearBackground(BLACK);
            
            BeginMode2D(cameraController.camera);
                DrawMap(gameMap);
                DrawRectangleV(player.position, player.size, player.color);
            EndMode2D();

            // UI elements
            DrawCircleV(GetMousePosition(), 4, DARKGRAY);
            DrawTextEx(GetFontDefault(), TextFormat("pxls [%i, %i]", GetMouseX(), GetMouseY()), 
                Vector2Add(GetMousePosition(), (Vector2){ -44, -24 }), 20, 2, RED);
            DrawTextEx(GetFontDefault(), TextFormat("zoom [%.2f]", cameraController.GetCameraZoom()), 
                Vector2Add(GetMousePosition(), (Vector2){ -44, -48 }), 20, 2, RED);
        
        EndDrawing();
    }

    // Cleanup
    UnloadAllTextures();
    CloseWindow();
    return 0;
}