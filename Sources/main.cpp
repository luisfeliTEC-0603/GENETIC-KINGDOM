#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"

#include "Game/game.hpp"
#include "System/camera.hpp"

// Towers
#include "Tower/tower.hpp"
#include "Tower/archer.hpp"
#include "Tower/artillery.hpp"
#include "Tower/wizard.hpp"

int main() {

    // === Environment Setup === 
    const int screenWidth = 1280;
    const int screenHeight = 640;
    InitWindow(screenWidth, screenHeight, "CE2103");
    SetTargetFPS(60);

    // === Game Objects Initialization ===
    vector<Tower*> towersList = {};
    vector<Enemy*> enemiesList = {};
    vector<Bullet> bullets;
    Coins coins;
    Information info;

    Map gameMap = LoadMapFromSaves("Saves/map.txt");
    if (gameMap.grid.empty()) {
        CloseWindow();
        return -1;
    }
    CameraController cameraController;
    cameraController.Initialize(screenWidth, screenHeight, gameMap);

    // === Enemy Example ===
    // Enemy* orc = newEnemy(gameMap, { 77, 35 }, EnemyType::Orc);
    // enemiesList.push_back(orc);
    // Enemy* mage = newEnemy(gameMap, { 21, 20 }, EnemyType::DarkMage);
    // enemiesList.push_back(mage);
    // Enemy* john_darkSouls = newEnemy(gameMap, { 42, 6 }, EnemyType::Undead);
    // enemiesList.push_back(john_darkSouls);
    // Enemy* sun_bro = newEnemy(gameMap, { 43, 6 }, EnemyType::Orc);
    // enemiesList.push_back(sun_bro);
    // Enemy* ezio  = newEnemy(gameMap, { 59, 48 }, EnemyType::Assassin);
    // enemiesList.push_back(ezio);

    // === Wave Control ===
    int waveNum = 1; 
    EnemyWave(gameMap, waveNum, enemiesList);

    // === Cell Info ===
    int cellValue = 0;

    // === Message Variables ===
    bool showMessage = false;
    float messageStartTime = 0;
    const float messageDuration = 2.0f;
    char messageText[64];

    // === GAME LOOP ===
    bool dead = false;
    while (!WindowShouldClose() && !dead) {

        // === System Data ===
        cameraController.Update(gameMap);
        Vector2 mouseCell = GetMouseCell(cameraController.camera, gameMap);
        float deltaTime = GetFrameTime();

        // === Game Logic ===
        bool showTowerMenu = false;

        // Defeat Condition
        for(Enemy* enemy : enemiesList){
            if (CheckDefeatCondition(*enemy, gameMap)) {
                BeginDrawing();
                    ClearBackground(BLACK);
                    DrawText("YOU DIED", screenWidth/2 - 100, screenHeight/2 - 20, 40, RED);
                EndDrawing();
                WaitTime(2);

                dead = true;
            }
        }

        // Logic to display game information
        if (IsKeyPressed(KEY_M)) {

            // Get towers information
            info.towers = {{{1, 0, 0, 0}, {2, 0, 0, 0}, {3, 0, 0, 0}}};
            for (int i = 0; i < (int)towersList.size(); i++) {
                int towerType = towersList[i]->getType();   
                int towerLevel = towersList[i]->getLevel() + 1; 

                if (towerType >= 1 && towerType <= 3 && towerLevel >= 1 && towerLevel <= 3) {
                    info.towers[towerType - 1][towerLevel]++;
                }
            }

            // Display screen 
            ShowInformationScreen(info);
            info.towers = {{{1, 0, 0, 0}, {2, 0, 0, 0}, {3, 0, 0, 0}}};
        }


        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            // Access to cell info:
            cellValue = gameMap.grid[(int)mouseCell.y][(int)mouseCell.x];
            if (cellValue == 1) {
                showTowerMenu = true; // Tower selection
            }

            if (cellValue == 5) {
                // Check which tower we are clicking
                for (int i = 0; i < (int)towersList.size(); i++) {
                    if (towersList[i]->getXpos() == (int)mouseCell.x && towersList[i]->getYpos() == (int)mouseCell.y) {

                        bool upg = UpgradeTower(towersList[i]->getLevel());
                        if (towersList[i]->getLevel() == 0  && upg) {

                            // Check if there are enough coins available.
                            if (coins.getCoinsAmount() >= 50) { 
                                coins.decreaseCoins(50);
                                towersList[i]->Upgrade1();
                                towersList[i]->increaseLevel();
                                break;
                            }

                            else{
                                sprintf(messageText, "NO ENOUGH COIN...");
                                showMessage = true;
                                messageStartTime = GetTime();
                                break;
                            }

                        }  

                        if (towersList[i]->getLevel() == 1  && upg) {
                            if (coins.getCoinsAmount() >= 100) {
                                coins.decreaseCoins(100);
                                towersList[i]->Upgrade2();
                                towersList[i]->increaseLevel();
                                break;
                            }

                            else{
                                sprintf(messageText, "NO ENOUGH COIN...");
                                showMessage = true;
                                messageStartTime = GetTime();
                                break;
                            }

                        }  

                        if (towersList[i]->getLevel() == 2  && upg) {
                            if (coins.getCoinsAmount() >= 150) {
                                coins.decreaseCoins(150);
                                towersList[i]->Upgrade3();
                                towersList[i]->increaseLevel();
                                break;
                            }
                            else{
                                sprintf(messageText, "NO ENOUGH COIN...");
                                showMessage = true;
                                messageStartTime = GetTime();
                                break;
                            }

                        }  

                        if (towersList[i]->getLevel() >= 3) {
                            sprintf(messageText, "MAX LEVEL TOWER");
                            showMessage = true;
                            messageStartTime = GetTime();
                        }  
                        break;
                    }
                }
            }
        }
        
        for (int i = (int)bullets.size() - 1; i >= 0; --i) {
            Bullet& b = bullets[i];
        
            // If the targetEnemy no longer exists (is nullptr) or whatever, you can ignore or remove it according to your logic.
            if (!b.selectedEnemy) {
                bullets.erase(bullets.begin() + i);
                continue;
            }
        
            // Distance between bullet and target
            float dx = b.position.x - (b.selectedEnemy->getWorldPosition().x + CELL_SIZE / 2);
            float dy = b.position.y - (b.selectedEnemy->getWorldPosition().y + CELL_SIZE / 2);
            float distance = sqrtf(dx * dx + dy * dy);
        
            // If it hits the enemy (set 5.0f as collision margin)
            if (distance <= 5.0f) {
                bullets.erase(bullets.begin() + i);
                bool enemyAlive = EnemyTakeHit(b.selectedEnemy);

                if (!enemyAlive) {
                    auto it = std::find(enemiesList.begin(), enemiesList.end(), b.selectedEnemy);
                    if (it != enemiesList.end()) {
                        
                        switch(b.selectedEnemy->getType()) {
                            case EnemyType::Orc:
                                coins.increasCoins(10);
                            case EnemyType::DarkMage:
                                coins.increasCoins(15);
                            case EnemyType::Undead:
                                coins.increasCoins(15);
                            case EnemyType::Assassin:
                                coins.increasCoins(20);
                        }
                        enemiesList.erase(it);
                    }
                
                    // We warn the bullets that this enemy no longer exists.
                    for (Bullet& otherBullet : bullets) {
                        if (otherBullet.selectedEnemy == b.selectedEnemy) {
                            otherBullet.selectedEnemy = nullptr;
                        }
                    }
                
                    delete b.selectedEnemy;
                }
                
            }
        
            // If bullet is on border delete it
            if (b.position.x < 0 || b.position.x > screenWidth ||
                b.position.y < 0 || b.position.y > screenHeight) {
                bullets.erase(bullets.begin() + i);
            }
        }

        // Check if waves is endded
        if (enemiesList.size() == 0) {
            waveNum++;
            EnemyWave(gameMap, waveNum, enemiesList);
        }
       
        BeginDrawing();
            ClearBackground(BLACK);
            
            // Sets Camera in 2D Mode
            BeginMode2D(cameraController.camera);

                DrawMap(gameMap);
                for(Enemy* enemy : enemiesList) {
                    UpdateEnemy(enemy, deltaTime);
                }

                // Check if an enemy is near each tower.
                for (int i = 0; i < (int)towersList.size(); i++) {
                    DrawTower(gameMap, towersList[i]->getXpos(), towersList[i]->getYpos(), towersList[i]->getType(), towersList[i]->getVision());
                    towersList[i]->CheckIfEnemiesInRange(enemiesList, bullets, deltaTime);
                }
                
                // This is in case player wants to add a new tower, can be cancelled
                if (showTowerMenu) {
                    int result = ShowScreen();
                    if (coins.getCoinsAmount() < 10) {
                        sprintf(messageText, "NO ENOUGH COIN... <( •̀ᴖ•́)>");
                        showMessage = true;
                        messageStartTime = GetTime();
                    }
                    else {
                        if (result != 0) {
                            // Aquí haces lo que necesites con el botón presionado
                            if (result == 1) {
                                coins.decreaseCoins(10);
                                towersList.push_back(new ArcherTower((int)mouseCell.x, (int)mouseCell.y, 5, 2, 7, 4, 1, 1, 1));
                                gameMap.grid[(int)mouseCell.y][(int)mouseCell.x] = 5; // 5 is an identificator that a tower has been asigned here.
                                // Archer Tower  
                            } else if (result == 2) {
                                coins.decreaseCoins(10);
                                towersList.push_back(new ArtilleryTower((int)mouseCell.x, (int)mouseCell.y, 7, 1, 3, 5, 2, 2, 1));
                                gameMap.grid[(int)mouseCell.y][(int)mouseCell.x] = 5;
                                // Whizar Tower
                            } else if (result == 3) {
                                coins.decreaseCoins(10);
                                towersList.push_back(new ArtilleryTower((int)mouseCell.x, (int)mouseCell.y, 10, 1, 3, 5, 2, 3, 1));
                                gameMap.grid[(int)mouseCell.y][(int)mouseCell.x] = 5;
                                // Artillery Tower
                            } else if (result == 4) {
                                // Cancel
                            }
                            showTowerMenu = false;
                        }
                    }
                }

                // this is made for bullet to be draw again
                for (int i = 0; i < (int)bullets.size(); i++) {
                    bullets[i].position.x += bullets[i].direction.x * bullets[i].speed;
                    bullets[i].position.y += bullets[i].direction.y * bullets[i].speed;
                    // Draw bullets depending on its type
                    if (bullets[i].type == 1) {
                        DrawCircleV(bullets[i].position, 2, BLACK);
                    }
                    else {
                        DrawCircleV(bullets[i].position, 2, WHITE);
                    }
                
                }

                // Show message
                if (showMessage) {
                    DrawRectangle(((int)mouseCell.x - 8) * CELL_SIZE , ((int)mouseCell.y - 8) * CELL_SIZE , 350, 50, RED);
                    DrawText(messageText, ((int)mouseCell.x - 7) * CELL_SIZE, ((int)mouseCell.y - 7) * CELL_SIZE, 20, WHITE); // 400 / 200
                
                    if (GetTime() - messageStartTime >= messageDuration) {
                        showMessage = false;
                    }
                }

            EndMode2D();
           
            // Data Collection-----
            DrawCircleV(GetMousePosition(), 4, DARKGRAY); // Exact Mouse Position

            DrawTextEx(GetFontDefault(),TextFormat("Currency[%i]", coins), 
                Vector2Add(GetMousePosition(), (Vector2){ -44, 72 }), 20, 2, RED); // Data : Actuall Currency
            
            DrawTextEx(GetFontDefault(), TextFormat("pxls [%i, %i]", GetMouseX(), GetMouseY()), 
                Vector2Add(GetMousePosition(), (Vector2){ -44, -24 }), 20, 2, RED); // Data : Mouse Coords

            DrawTextEx(GetFontDefault(), TextFormat("zoom [%.2f]", cameraController.GetCameraZoom()), 
                Vector2Add(GetMousePosition(), (Vector2){ -44, -48 }), 20, 2, RED); // Data : Zoom Level
            
            DrawTextEx(GetFontDefault(), TextFormat("cell [%i, %i]", (int)mouseCell.x, (int)mouseCell.y), 
                Vector2Add(GetMousePosition(), (Vector2){ -44, 24 }), 20, 2, RED); // Data : Mouse in Cell

        EndDrawing();
    }

    // Cleanup
    for(Enemy* enemy : enemiesList) { delete enemy; }
    for(Tower* tower : towersList) { delete tower; }
    UnloadAllTextures();
    UnloadRenderTexture(gameMap.renderTexture);
    CloseWindow();
    
    return 0;
}
