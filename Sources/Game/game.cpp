#include "game.hpp"

Enemy* newEnemy(const Map& map, const Vector2& start, EnemyType type) {
    
    Enemy* enemy = new Enemy(
        start,
        { (float)ENEMY_SIZE, (float)ENEMY_SIZE },
        PLAYER_COLOR,
        type,
        50.0f
    );
    
    std::vector<Vector2> path = AStarPathfinder::findPath(map.grid, start, map.goal);
    if (!path.empty()) {
        std::vector<Vector2> worldPath;
        
        for (const auto& gridPos : path) {
            Vector2 worldPos = {
                gridPos.x * CELL_SIZE + (CELL_SIZE - ENEMY_SIZE) / 2,
                gridPos.y * CELL_SIZE + (CELL_SIZE - ENEMY_SIZE) / 2
            };
            worldPath.push_back(worldPos);
        }

        enemy->setPathway(worldPath);
    }

    return enemy;
}

void DrawPathway(const Enemy& enemy, Color pathColor) {
    const std::vector<Vector2>& path = enemy.getPathway();
    
    if (path.empty()) {
        Vector2 warningPos = { 
            enemy.getWorldPosition().x - enemy.getSize().x, enemy.getWorldPosition().y - enemy.getSize().y };
        DrawText("NO PATH!", warningPos.x, warningPos.y, 10, pathColor);
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
}

void UpdateEnemy(Enemy* enemy, const float deltaTime) {
    std::vector<Vector2> path = enemy->getPathway();
    if (path.empty()) return;

    float speed = enemy->getSpeed();
    size_t index = enemy->getStep();
    float progress = enemy->getStepProgress();

    if (path.size() > 1 && index < path.size() - 1) {
        Vector2 current = path[index];
        Vector2 next = path[index + 1];

        float distance = Vector2Distance(current, next);
        float moveAmount = speed * deltaTime;
        progress += moveAmount / distance;

        if (progress >= 1.0f) {
            enemy->setStepProgress(0.0f);
            enemy->setStep(index + 1);
            
            if (index + 1 >= path.size() - 1) {
                enemy->setWorldPosition(path.back());
                path.clear();
                return;
            }
        } else {
            Vector2 newPos = Vector2Lerp(current, next, progress);
            enemy->setWorldPosition(newPos);
            enemy->setStepProgress(progress);
        }

    } else {
        enemy->setWorldPosition(path.back());
        path.clear();
    }
}

bool CheckDefeatCondition(const Enemy& enemy, const Map& map) {
    Rectangle enemyRect = {enemy.getWorldPosition().x, enemy.getWorldPosition().y, enemy.getSize().x, enemy.getSize().y};
    Rectangle goalRect = {map.goal.x * CELL_SIZE, map.goal.y * CELL_SIZE, (float)CELL_SIZE, (float)CELL_SIZE};
    
    return CheckCollisionRecs(enemyRect, goalRect);
}