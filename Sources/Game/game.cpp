#include "game.hpp"
#include <iostream>

Enemy* newEnemy(const Map& map, const Vector2& start) {
    // Debug: Print initialization parameters
    std::cout << "\n===== Creating new Enemy =====\n";
    std::cout << "Start position (grid): (" << start.x << ", " << start.y << ")\n";
    std::cout << "Goal position (grid): (" << map.goal.x << ", " << map.goal.y << ")\n";
    std::cout << "Player size: " << PLAYER_SIZE << "\n";
    std::cout << "Cell size: " << CELL_SIZE << "\n";

    Enemy* enemy = new Enemy(
        start,
        { (float)PLAYER_SIZE, (float)PLAYER_SIZE },
        PLAYER_COLOR,
        2.0f
    );

    // Debug: Print enemy creation confirmation
    std::cout << "Enemy created at grid position: (" 
              << enemy->getGridPosition().x << ", " 
              << enemy->getGridPosition().y << ")\n";

    std::vector<Vector2> path = AStarPathfinder::findPath(map.grid, start, map.goal);
    
    // Debug: Print pathfinding results
    std::cout << "\nPathfinding results:\n";
    std::cout << "Path length: " << path.size() << "\n";
    for (size_t i = 0; i < path.size(); i++) {
        std::cout << "  Point " << i << ": (" << path[i].x << ", " << path[i].y << ")\n";
    }

    if (!path.empty()) {
        std::vector<Vector2> worldPath;
        // Debug: Print coordinate conversion header
        std::cout << "\nConverting grid to world coordinates:\n";
        
        for (const auto& gridPos : path) {
            Vector2 worldPos = {
                gridPos.x * CELL_SIZE + (CELL_SIZE - PLAYER_SIZE) / 2,
                gridPos.y * CELL_SIZE + (CELL_SIZE - PLAYER_SIZE) / 2
            };
            worldPath.push_back(worldPos);

            // Debug: Print each conversion
            std::cout << "  Grid (" << gridPos.x << ", " << gridPos.y << ") -> World (" 
                      << worldPos.x << ", " << worldPos.y << ")\n";
        }
        enemy->setPathway(worldPath);

        // Debug: Print final pathway
        std::cout << "\nFinal pathway set with " << worldPath.size() << " points:\n";
        for (const auto& point : worldPath) {
            std::cout << "  (" << point.x << ", " << point.y << ")\n";
        }
    } else {
        std::cout << "WARNING: No path found from start to goal!\n";
    }
    
    std::cout << "===== Enemy creation complete =====\n\n";
    return enemy;
}

void DrawPathway(const Enemy& enemy, Color pathColor) {
    const std::vector<Vector2>& path = enemy.getPathway();
    
    if (path.empty()) {
        // Draw warning indicator above enemy
        Vector2 warningPos = { enemy.getWorldPosition().x, enemy.getWorldPosition().y - 30 };
        
        // Triangle warning sign
        DrawTriangle(
            {warningPos.x, warningPos.y - 15},
            {warningPos.x - 10, warningPos.y + 10},
            {warningPos.x + 10, warningPos.y + 10},
            YELLOW
        );
        
        // Exclamation mark
        DrawRectangle(warningPos.x - 2, warningPos.y - 5, 4, 10, YELLOW);
        DrawRectangle(warningPos.x - 2, warningPos.y + 10, 4, 4, YELLOW);
        
        // Text label
        DrawText("NO PATH", warningPos.x - 30, warningPos.y + 20, 10, YELLOW);
        return;
    }

    for (size_t i = 0; i < path.size() - 1; i++) {
        Vector2 start = {
            path[i].x * CELL_SIZE + (CELL_SIZE - enemy.getSize().x) / 2,
            path[i].y * CELL_SIZE + (CELL_SIZE - enemy.getSize().y) / 2
        };
        Vector2 end = {
            path[i+1].x * CELL_SIZE + (CELL_SIZE - enemy.getSize().x) / 2,
            path[i+1].y * CELL_SIZE + (CELL_SIZE - enemy.getSize().y) / 2
        };
        DrawLineEx(start, end, 2.0f, pathColor);
    }
}

void UpdateEnemy(Enemy& enemy, const Map& map) {
    Vector2 newPosition = enemy.getWorldPosition();
    Vector2 velocity = {0, 0};
    float speed = enemy.getSpeed();

    DrawPathway(enemy, BLACK);
    
    // Get input (with delta time for smooth movement)
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) velocity.x = speed;
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) velocity.x = -speed;
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) velocity.y = -speed;
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) velocity.y = speed;
    
    // Calculate new position
    newPosition.x += velocity.x;
    newPosition.y += velocity.y;
    
    // Check collision with walls
    bool canMove = true;
    
    // Enemy bounds in WORLD coordinates
    Rectangle EnemyRect = {newPosition.x, newPosition.y, enemy.getSize().x, enemy.getSize().y};

    // Check each cell around the Enemy
    for (int y = 0; y < map.height && canMove; y++) {
        for (int x = 0; x < map.width && canMove; x++) {
            if (map.grid[y][x] == 1) { // If it's a wall
                Rectangle wallRect = {
                    (float)x * CELL_SIZE, 
                    (float)y * CELL_SIZE, 
                    (float)CELL_SIZE, 
                    (float)CELL_SIZE
                };
                if (CheckCollisionRecs(EnemyRect, wallRect)) {
                    canMove = false;
                }
            }
        }
    }
    
    // Check world bounds
    if (newPosition.x < 0 || newPosition.x + enemy.getSize().x > map.width * CELL_SIZE ||
        newPosition.y < 0 || newPosition.y + enemy.getSize().y > map.height * CELL_SIZE) {
        canMove = false;
    }
    
    // Update position if no collision
    if (canMove) {
        enemy.setWorldPosition(newPosition);
    }
}

bool CheckWinCondition(const Enemy& enemy, const Map& map) {
    Rectangle enemyRect = {enemy.getWorldPosition().x, enemy.getWorldPosition().y, enemy.getSize().x, enemy.getSize().y};
    Rectangle goalRect = {map.goal.x * CELL_SIZE, map.goal.y * CELL_SIZE, (float)CELL_SIZE, (float)CELL_SIZE};
    
    return CheckCollisionRecs(enemyRect, goalRect);
}