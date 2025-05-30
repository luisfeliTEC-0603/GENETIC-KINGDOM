#include "game.hpp"

Enemy* newEnemy(const Map& map, const Vector2& start, EnemyType type) {
    
    Enemy* enemy = new Enemy(
        start,
        { (float)ENEMY_SIZE, (float)ENEMY_SIZE },
        type
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

void DrawEnemy(Enemy* enemy, Color color) {

    Vector2 pos = enemy->getWorldPosition();
    Vector2 size = enemy->getSize();

    Rectangle rect = {
        pos.x, pos.y,
        size.x, size.y
    };

    Texture2D texture;
    switch (enemy->getType()) {
        case EnemyType::Orc: texture = GameTextures::orc; break;
        case EnemyType::DarkMage: texture = GameTextures::darkMage; break;
        case EnemyType::Undead: texture = GameTextures::undead; break;
        case EnemyType::Assassin: texture = GameTextures::assassin; break;
    }

    DrawTexturePro(
        texture,
        {size.x * enemy->getWalkFrame(), size.y *static_cast<int>(enemy->getDirection()), size.x, size.y }, 
        rect, {0.0f, 0.0f}, 0.0f, color);
}

void UpdateEnemy(Enemy* enemy, const float deltaTime) {
    std::vector<Vector2> path = enemy->getPathway();
    if (path.empty()) return;

    float speed = enemy->getSpeed();
    size_t index = enemy->getStep();
    float progress = enemy->getStepProgress();
   
    DrawEnemy(enemy, WHITE);

    //static int animCounter = 0;
    //static const int slowFactor = 3;
    //if (++animCounter >= slowFactor) {
    //    enemy->setWalkFrame((enemy->getWalkFrame() + 1) % 5);
    //    animCounter = 0;
    //}

    enemy->setWalkFrame(RandomUtils::randomInt(0, 4));

    if (path.size() > 1 && index < path.size() - 1) {
        Vector2 current = path[index];
        Vector2 next = path[index + 1];

        Vector2 direction = Vector2Normalize(Vector2Subtract(next, current));
        EnemyDirection eDir;
        
        if (direction.x > 0.7f)        eDir = EnemyDirection::right;
        else if (direction.x < -0.7f)  eDir = EnemyDirection::left;
        else if (direction.y > 0.7f)   eDir = EnemyDirection::down;
        else if (direction.y < -0.7f)  eDir = EnemyDirection::up;
        else {
            if (fabs(direction.x) > fabs(direction.y)) {
                eDir = (direction.x > 0) ? EnemyDirection::right : EnemyDirection::left;
            } else {
                eDir = (direction.y > 0) ? EnemyDirection::down : EnemyDirection::up;
            }
        }
        enemy->setDirection(eDir);

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

bool EnemyTakeHit(Enemy* enemy, int bulletType, int damage) {

    // Invalid Enemy pointer
    if (!enemy) { return false; }

    int damageFactor = damage;
    const std::vector<int>& resistantTypes = enemy->getResistances();

    // Cases for resistances 
    if(std::find(resistantTypes.begin(), resistantTypes.end(), bulletType) != resistantTypes.end()){
        damageFactor /= 2; 
    }
   
    int newHealth = std::max(0, enemy->getHealth() - damageFactor);
    DrawEnemy(enemy, RED);
    enemy->setHealth(newHealth);

    return newHealth > 0; // Still alive ?
}

bool CheckDefeatCondition(const Enemy& enemy, const Map& map) {
    Rectangle enemyRect = {enemy.getWorldPosition().x, enemy.getWorldPosition().y, enemy.getSize().x, enemy.getSize().y};
    Rectangle goalRect = {map.goal.x * CELL_SIZE, map.goal.y * CELL_SIZE, (float)CELL_SIZE, (float)CELL_SIZE};
    
    return CheckCollisionRecs(enemyRect, goalRect);
}

void EnemyWave(const Map& map, int waveNum, std::vector<Enemy*>& enemiesList, GeneticManager& geneticMan) {
    int enemiesNum = std::max(1, 5 + waveNum); 

    int maxIndex = static_cast<int>(map.start.size());
    
    for (int i = 0; i < enemiesNum; i++) {
        int positionIndex = RandomUtils::randomInt(0, maxIndex-1); 
        int type = RandomUtils::randomInt(0, 3);
        EnemyType randomType = static_cast<EnemyType>(type);
        
        Enemy* enemy = newEnemy(map, map.start[positionIndex], randomType);

        // New stats for enemy
        int newHealth = geneticMan.getHealthFrom(type);
        int newSpeed = geneticMan.getSpeedFrom(type);

        if (RandomUtils::checkProbability(geneticMan.getProbMut() / 100.0f)){ // health mutation
            geneticMan.IncreaseMutation();
            newSpeed = newSpeed + RandomUtils::randomInt(1, 3);
        }

        if (RandomUtils::checkProbability(geneticMan.getProbMut() / 100.0f)){ // health mutation
            geneticMan.IncreaseMutation();
            newHealth = newHealth + RandomUtils::randomInt(4, 7);
        }

        geneticMan.changeNewStat(type, newHealth, newSpeed);
        enemy->setHealth(newHealth);
        enemy->setSpeed(newSpeed);
        std::cout << "Tipo: " << type << " | Position: " << positionIndex << " | Healt: " << newHealth <<" | Speed: "  << newSpeed << std::endl;

        enemiesList.push_back(enemy);
    }
}
