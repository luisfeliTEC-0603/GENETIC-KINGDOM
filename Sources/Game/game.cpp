#include "game.hpp"
#include "raylib.h"
// #include "Pathfinding/aStar.cpp"

void UpdateEnemy(Enemy& enemy, const Map& map) {
    Vector2 newPosition = enemy.position;
    Vector2 velocity = {0, 0};
    float speed = enemy.speed;
    
    // Get input
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) velocity.x = speed;
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) velocity.x = -speed;
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) velocity.y = -speed;
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) velocity.y = speed;
    
    // Calculate new position
    newPosition.x += velocity.x;
    newPosition.y += velocity.y;
    
    // Check collision with walls
    bool canMove = true;
    
    // Enemy bounds
    Rectangle EnemyRect = {newPosition.x, newPosition.y, enemy.size.x, enemy.size.y};
    
    // Check each cell around the Enemy
    for (int y = 0; y < map.height && canMove; y++) {
        for (int x = 0; x < map.width && canMove; x++) {
            if (map.grid[y][x] == 1) { // If it's a wall
                Rectangle wallRect = {(float)x * CELL_SIZE, (float)y * CELL_SIZE, (float)CELL_SIZE, (float)CELL_SIZE};
                if (CheckCollisionRecs(EnemyRect, wallRect)) {
                    canMove = false;
                }
            }
        }
    }
    
    // Also check bounds of the map
    if (newPosition.x < 0 || newPosition.x + enemy.size.x > map.width * CELL_SIZE ||
        newPosition.y < 0 || newPosition.y + enemy.size.y > map.height * CELL_SIZE) {
        canMove = false;
    }
    
    // Update position if no collision
    if (canMove) {
        enemy.position = newPosition;
    }
}

bool CheckWinCondition(const Enemy& Enemy, const Map& map) {
    Rectangle EnemyRect = {Enemy.position.x, Enemy.position.y, Enemy.size.x, Enemy.size.y};
    Rectangle goalRect = {map.goal.x * CELL_SIZE, map.goal.y * CELL_SIZE, (float)CELL_SIZE, (float)CELL_SIZE};
    
    return CheckCollisionRecs(EnemyRect, goalRect);
}