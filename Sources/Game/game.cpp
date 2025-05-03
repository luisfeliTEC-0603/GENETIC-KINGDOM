#include "game.hpp"

Enemy* newEnemy(const Map& map, const Vector2& start) {
    // Convert grid position to pixel position
    Vector2 pixelPosition = {
        (float)start.x * CELL_SIZE + (CELL_SIZE - PLAYER_SIZE) / 2, 
        (float)start.y * CELL_SIZE + (CELL_SIZE - PLAYER_SIZE) / 2
    };
    
    Enemy* enemy = new Enemy(
        pixelPosition,
        { (float)PLAYER_SIZE, (float)PLAYER_SIZE },
        PLAYER_COLOR, 
        2.0f
    );
    
    Vector2 gridStart = { start.x, start.y };
    Vector2 gridGoal = { map.goal.x / CELL_SIZE,map.goal.y / CELL_SIZE };
    
    std::vector<Vector2> path = AStarPathfinder::findPath(map.grid, gridStart, gridGoal);
    
    if (!path.empty()) {
        std::vector<Vector2> worldPath;
        for (const auto& gridPos : path) {
            worldPath.push_back({
                gridPos.x * CELL_SIZE + (CELL_SIZE - PLAYER_SIZE) / 2,
                gridPos.y * CELL_SIZE + (CELL_SIZE - PLAYER_SIZE) / 2
            });
        }
        enemy->setPathway(worldPath);
    }
    
    return enemy;
}

void UpdateEnemy(Enemy& enemy, const Map& map) {
    Vector2 newPosition = enemy.getPosition();
    Vector2 velocity = {0, 0};
    float speed = enemy.getSpeed();
    
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
    Rectangle EnemyRect = {newPosition.x, newPosition.y, enemy.getSize().x, enemy.getSize().y};
    
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
    if (newPosition.x < 0 || newPosition.x + enemy.getSize().x > map.width * CELL_SIZE ||
        newPosition.y < 0 || newPosition.y + enemy.getSize().y > map.height * CELL_SIZE) {
        canMove = false;
    }
    
    // Update position if no collision
    if (canMove) {
        enemy.setPosition(newPosition);
    }
}

bool CheckWinCondition(const Enemy& enemy, const Map& map) {
    Rectangle enemyRect = {enemy.getPosition().x, enemy.getPosition().y, enemy.getSize().x, enemy.getSize().y};
    Rectangle goalRect = {map.goal.x * CELL_SIZE, map.goal.y * CELL_SIZE, (float)CELL_SIZE, (float)CELL_SIZE};
    
    return CheckCollisionRecs(enemyRect, goalRect);
}