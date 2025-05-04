#include "game.hpp"
#include <iostream>

Enemy* newEnemy(const Map& map, const Vector2& start) {
    // Debug: Print initialization parameters
    std::cout << "\n===== Creating new Enemy =====\n";
    std::cout << "Start position (grid): (" << start.x << ", " << start.y << ")\n";
    std::cout << "Goal position (grid): (" << map.goal.x << ", " << map.goal.y << ")\n";
    std::cout << "Player size: " << ENEMY_SIZE << "\n";
    std::cout << "Cell size: " << CELL_SIZE << "\n";

    Enemy* enemy = new Enemy(
        start,
        { (float)ENEMY_SIZE, (float)ENEMY_SIZE },
        PLAYER_COLOR,
        50.0f
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
                gridPos.x * CELL_SIZE + (CELL_SIZE - ENEMY_SIZE) / 2,
                gridPos.y * CELL_SIZE + (CELL_SIZE - ENEMY_SIZE) / 2
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

    // Draw path lines
    for (size_t i = 0; i < path.size() - 1; i++) {
        Vector2 start = {
            path[i].x + enemy.getSize().x/2,
            path[i].y + enemy.getSize().y/2
        };
        Vector2 end = {
            path[i+1].x + enemy.getSize().x/2,
            path[i+1].y + enemy.getSize().y/2
        };
        DrawLineEx(start, end, 2.0f, pathColor);
    }

    // Draw path points
    for (const Vector2& point : path) {
        Vector2 center = {
            point.x + enemy.getSize().x/2,
            point.y + enemy.getSize().y/2
        };
        DrawCircleV(center, 3.0f, pathColor);
    }

    // Draw start (green) and end (red) markers
    if (!path.empty()) {
        // Start marker
        Vector2 start = {
            path.front().x + enemy.getSize().x/2,
            path.front().y + enemy.getSize().y/2
        };
        DrawCircleV(start, 5.0f, GREEN);
        
        // End marker
        Vector2 end = {
            path.back().x + enemy.getSize().x/2,
            path.back().y + enemy.getSize().y/2
        };
        DrawCircleV(end, 5.0f, RED);
    }
}

void UpdateEnemy(Enemy& enemy, const float deltaTime) {
    std::vector<Vector2> path = enemy.getPathway();
    if (path.empty()) return;

    float speed = enemy.getSpeed();
    size_t index = enemy.getStep();
    float progress = enemy.getStepProgress();

    if (path.size() > 1 && index < path.size() - 1) {
        Vector2 current = path[index];
        Vector2 next = path[index + 1];

        float distance = Vector2Distance(current, next);
        float moveAmount = speed * deltaTime;
        progress += moveAmount / distance;

        if (progress >= 1.0f) {
            enemy.setStepProgress(0.0f);
            enemy.setStep(index + 1);
            
            if (index + 1 >= path.size() - 1) {
                enemy.setWorldPosition(path.back());
                path.clear();
                return;
            }
        } else {
            Vector2 newPos = Vector2Lerp(current, next, progress);
            enemy.setWorldPosition(newPos);
            enemy.setStepProgress(progress);
        }

    } else {
        enemy.setWorldPosition(path.back());
        path.clear();
    }
}

bool CheckWinCondition(const Enemy& enemy, const Map& map) {
    Rectangle enemyRect = {enemy.getWorldPosition().x, enemy.getWorldPosition().y, enemy.getSize().x, enemy.getSize().y};
    Rectangle goalRect = {map.goal.x * CELL_SIZE, map.goal.y * CELL_SIZE, (float)CELL_SIZE, (float)CELL_SIZE};
    
    return CheckCollisionRecs(enemyRect, goalRect);
}