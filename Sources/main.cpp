#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include <vector>
#include <iostream>



#include "Game/game.hpp"
#include "System/camera.hpp"

// Towers
#include "Tower/tower.hpp"
#include "Tower/archer.hpp"
#include "Tower/artillery.hpp"
#include "Tower/whizard.hpp"


int main() {

    // Initialization
    const int screenWidth = 1280;
    const int screenHeight = 640;

    // Game objects
    // Vector with towers that are on map and towerID to recognize each tower when deletting bullets

    vector<Tower*> towers = {};
    int towerID = 0;

    // Vector with Enemies deployed on game map
    vector<Enemy> enemys = {};

    // Vector with current bullets on map
    vector<Bullet> bullets;

    // Currency of the game
    Coins coins;
    
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
        {(float)gameMap.start.x * CELL_SIZE +32*CELL_SIZE+(CELL_SIZE - PLAYER_SIZE) / 2, 
         (float)gameMap.start.y * CELL_SIZE +32*CELL_SIZE+(CELL_SIZE - PLAYER_SIZE) / 2},
        {(float)PLAYER_SIZE, (float)PLAYER_SIZE},
        PLAYER_COLOR, 2.0f
    };
    enemys.push_back(player); // This must be deleted since it is used for example. 

    // Type info variable <Set in Right Click>
    int cellValue = -1;

    // Game Loop
    while (!WindowShouldClose()) {

        // System----- (-> System/camera.hpp)
        cameraController.Update(gameMap);
        Vector2 mouseCell = GetMouseCell(cameraController.camera, gameMap);
        float deltaTime = GetFrameTime(); // Iniciatize time, used for shooting logic 

        // Game logic-----
        UpdateEnemy(player, gameMap);
        bool showTowerMenu = false;

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
            if (cellValue == 1) {
                showTowerMenu = true;
            }
        }
        
        // Erase bullets needed logic to colide with enemy
        for (int i = (int)bullets.size() - 1; i >= 0; i--) {
            if (bullets[i].position.x < 0 || bullets[i].position.x > screenWidth ||
                bullets[i].position.y < 0 || bullets[i].position.y > screenHeight) {
                    
                bullets.erase(bullets.begin() + i);
            }
        }
        

        // Graphics-----
        BeginDrawing();

            ClearBackground(BLACK);
            
            // Sets Camera in 2D Mode
            BeginMode2D(cameraController.camera);

                DrawMap(gameMap);
                DrawRectangleV(player.position, player.size, player.color);

                // Check if an enemy is near each tower.
                for (int i = 0; i < (int)towers.size(); i++) {
                    DrawTower(gameMap, towers[i]->getXpos(), towers[i]->getYpos(), towers[i]->getType());
                    towers[i]->CheckIfEnemyesInRange(enemys, bullets, deltaTime);
                }
                
                // This is in case player wants to add a new tower, can be cancelled
                if (showTowerMenu) {
                    int result = ShowScreen();
                    if (result != 0) {
                        // Aquí haces lo que necesites con el botón presionado
                        if (result == 1) {
                            coins.decreasCoins(10);
                            towers.push_back(new ArcherTower((int)mouseCell.x, (int)mouseCell.y, 5, 2, 7, 4, 1, 1, towerID));
                            towerID++;
                            // Archer Tower  
                        } else if (result == 2) {
                            coins.decreasCoins(10);
                            towers.push_back(new ArtilleryTower((int)mouseCell.x, (int)mouseCell.y, 7, 5, 3, 5, 2, 2, towerID));
                            towerID++;
                            // Whizar Tower
                        } else if (result == 3) {
                            coins.decreasCoins(10);
                            towers.push_back(new ArtilleryTower((int)mouseCell.x, (int)mouseCell.y, 10, 2, 3, 5, 2, 3, towerID));
                            towerID++;
                            // Artillery Tower
                        } else if (result == 4) {
                            // Cnancel
                        }
                        showTowerMenu = false;
                    }
                }

                // this is made for bullet to be draw again
                for (int i = 0; i < (int)bullets.size(); i++) {
                    bullets[i].position.x += bullets[i].direction.x * bullets[i].speed;
                    bullets[i].position.y += bullets[i].direction.y * bullets[i].speed;
                
                    // Draw bullets
                    DrawCircleV(bullets[i].position, 3, RED);
                
                }

            EndMode2D();

            // Data Collection-----
            DrawCircleV(GetMousePosition(), 4, DARKGRAY); // Exact Mouse Position
            
            DrawTextEx(GetFontDefault(), TextFormat("pxls [%i, %i]", GetMouseX(), GetMouseY()), 
                Vector2Add(GetMousePosition(), (Vector2){ -44, -24 }), 20, 2, RED); // Data : Mouse Coords

            DrawTextEx(GetFontDefault(), TextFormat("zoom [%.2f]", cameraController.GetCameraZoom()), 
                Vector2Add(GetMousePosition(), (Vector2){ -44, -48 }), 20, 2, RED); // Data : Zoom Level
            
            DrawTextEx(GetFontDefault(), TextFormat("cell [%i, %i]", (int)mouseCell.x, (int)mouseCell.y), 
                Vector2Add(GetMousePosition(), (Vector2){ -44, 24 }), 20, 2, RED); // Data : Mouse in Cell

            DrawTextEx(GetFontDefault(), TextFormat("cell-info [%i]", (int)bullets.size()), 
                Vector2Add(GetMousePosition(), (Vector2){ -44, 48 }), 20, 2, RED); // Data : Mouse in Cell

        EndDrawing();
    }

    // Cleanup
    UnloadAllTextures(); // Finalize Textures -> gameTextures.hpp
    CloseWindow();
    return 0;
}