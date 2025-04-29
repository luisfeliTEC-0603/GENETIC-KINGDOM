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
    
    SetTargetFPS(60); // Set FPS

    Map gameMap = LoadMapFromSaves("Saves/map.txt"); // Access Saved Files
    if (gameMap.grid.empty()) {
        CloseWindow();
        return -1;
    }

    // Initialize Camera -> System/camera.hpp
    CameraController cameraController;
    cameraController.Initialize(screenWidth, screenHeight, gameMap);

    // Enemy Sample -> gameEnemies.hpp
    Enemy player = {
        {(float)gameMap.start.x * CELL_SIZE + (CELL_SIZE - PLAYER_SIZE) / 2, 
         (float)gameMap.start.y * CELL_SIZE + (CELL_SIZE - PLAYER_SIZE) / 2},
        {(float)PLAYER_SIZE, (float)PLAYER_SIZE},
        PLAYER_COLOR, 2.0f
    };

    // Type info variable <Set in Right Click>
    int cellValue = -1;

    // Game Loop
    while (!WindowShouldClose()) {

        // System----- (-> System/camera.hpp)
        cameraController.Update(gameMap);
        Vector2 mouseCell = GetMouseCell(cameraController.camera, gameMap);

        // Game logic-----
        UpdateEnemy(player, gameMap);

        // Check Collision
        if (CheckWinCondition(player, gameMap)) {
            BeginDrawing();
                ClearBackground(BLACK);
                DrawText("You Win!", screenWidth/2 - 100, screenHeight/2 - 20, 40, GREEN);
            EndDrawing();
            WaitTime(2);
            break;
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {

            // Access to cell info:
            cellValue = gameMap.grid[(int)mouseCell.y][(int)mouseCell.x];
        }

        // Graphics-----
        BeginDrawing();

            ClearBackground(BLACK);
            
            // Sets Camera in 2D Mode
            BeginMode2D(cameraController.camera);

                DrawMap(gameMap);
                DrawRectangleV(player.position, player.size, player.color);

            EndMode2D();

            // Data Collection-----
            DrawCircleV(GetMousePosition(), 4, DARKGRAY); // Exact Mouse Position
            
            DrawTextEx(GetFontDefault(), TextFormat("pxls [%i, %i]", GetMouseX(), GetMouseY()), 
                Vector2Add(GetMousePosition(), (Vector2){ -44, -24 }), 20, 2, RED); // Data : Mouse Coords

            DrawTextEx(GetFontDefault(), TextFormat("zoom [%.2f]", cameraController.GetCameraZoom()), 
                Vector2Add(GetMousePosition(), (Vector2){ -44, -48 }), 20, 2, RED); // Data : Zoom Level
            
            DrawTextEx(GetFontDefault(), TextFormat("cell [%i, %i]", (int)mouseCell.x, (int)mouseCell.y), 
                Vector2Add(GetMousePosition(), (Vector2){ -44, 24 }), 20, 2, RED); // Data : Mouse in Cell

            DrawTextEx(GetFontDefault(), TextFormat("cell-info [%i]", cellValue), 
                Vector2Add(GetMousePosition(), (Vector2){ -44, 48 }), 20, 2, RED); // Data : Mouse in Cell

        EndDrawing();
    }

    // Cleanup
    UnloadAllTextures(); // Finalize Textures -> gameTextures.hpp
    CloseWindow();
    return 0;
}