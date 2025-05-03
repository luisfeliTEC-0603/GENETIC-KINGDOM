#include "aStar.hpp"

// Node implementation
PathNode::PathNode() : 
    position({-1, -1}), 
    parent({-1, -1}), 
    f(std::numeric_limits<float>::max()),
    g(std::numeric_limits<float>::max()),
    h(0),
    closed(false),
    open(false) {}

PathNode::PathNode(Vector2 pos) : 
    position(pos), 
    parent({-1, -1}), 
    f(std::numeric_limits<float>::max()),
    g(std::numeric_limits<float>::max()),
    h(0),
    closed(false),
    open(false) {}

namespace Pathfinding {

float calculateHeuristic(Vector2 a, Vector2 b) {
    // Octile distance for more natural diagonal movement
    float dx = std::abs(a.x - b.x);
    float dy = std::abs(a.y - b.y);
    return (dx + dy) + (1.414f - 2) * std::min(dx, dy);
}

std::vector<Vector2> smoothPath(const std::vector<Vector2>& path, WalkableCheck isWalkable) {
    if (path.size() < 3) return path;
    
    std::vector<Vector2> smoothedPath;
    smoothedPath.push_back(path[0]);
    
    size_t lastValid = 0;
    for (size_t i = 2; i < path.size(); i++) {
        Vector2 start = path[lastValid];
        Vector2 end = path[i];
        
        // Check line of sight
        bool hasLOS = true;
        Vector2 delta = end - start;
        float steps = std::max(std::abs(delta.x), std::abs(delta.y));
        delta = delta / steps;
        
        Vector2 current = start;
        for (float t = 0; t <= steps && hasLOS; t++) {
            if (!isWalkable((int)std::round(current.x), (int)std::round(current.y))) {
                hasLOS = false;
            }
            current = current + delta;
        }
        
        if (!hasLOS) {
            smoothedPath.push_back(path[i-1]);
            lastValid = i-1;
        }
    }
    
    smoothedPath.push_back(path.back());
    return smoothedPath;
}

std::vector<Vector2> reconstructPath(Vector2 start, Vector2 goal, std::vector<std::vector<PathNode>>& nodeGrid) {
    std::vector<Vector2> path;
    Vector2 current = goal;
    
    while (!(current.x == start.x && current.y == start.y)) {
        path.push_back(current);
        current = nodeGrid[(int)current.y][(int)current.x].parent;
        
        if (current.x == -1 && current.y == -1) {
            return {};
        }
    }
    
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<Vector2> findPath(
    Vector2 start,
    Vector2 goal,
    WalkableCheck isWalkable,
    MapDimensions getDimensions,
    bool shouldSmoothPath
) {
    auto path = findPathWithCost(
        start,
        goal,
        isWalkable,
        getDimensions,
        [](Vector2, Vector2) { return 1.0f; }
    );
    
    return shouldSmoothPath ? smoothPath(path, isWalkable) : path;
}

std::vector<Vector2> findPathWithCost(
    Vector2 start,
    Vector2 goal,
    WalkableCheck isWalkable,
    MapDimensions getDimensions,
    std::function<float(Vector2, Vector2)> costFunc,
    bool shouldSmoothPath
) {
    // Get map dimensions
    int mapWidth, mapHeight;
    getDimensions(mapWidth, mapHeight);

    // Initialize node grid
    std::vector<std::vector<PathNode>> nodeGrid(mapHeight, std::vector<PathNode>(mapWidth));
    for (int y = 0; y < mapHeight; y++) {
        for (int x = 0; x < mapWidth; x++) {
            nodeGrid[y][x] = PathNode({(float)x, (float)y});
        }
    }

    // Check if start or goal are valid
    if (!isWalkable((int)start.x, (int)start.y) || !isWalkable((int)goal.x, (int)goal.y)) {
        return {};
    }

    // Priority queue for open set
    auto cmp = [&nodeGrid](Vector2 left, Vector2 right) {
        return nodeGrid[(int)left.y][(int)left.x].f > nodeGrid[(int)right.y][(int)right.x].f;
    };
    std::priority_queue<Vector2, std::vector<Vector2>, decltype(cmp)> openSet(cmp);

    // Initialize start node
    PathNode& startNode = nodeGrid[(int)start.y][(int)start.x];
    startNode.g = 0;
    startNode.h = calculateHeuristic(start, goal);
    startNode.f = startNode.h;
    startNode.open = true;
    openSet.push(start);

    // 8-directional movement
    const Vector2 directions[8] = {
        {1,0}, {0,1}, {-1,0}, {0,-1},  // Cardinal
        {1,1}, {-1,1}, {1,-1}, {-1,-1} // Diagonal
    };

    while (!openSet.empty()) {
        Vector2 currentPos = openSet.top();
        openSet.pop();
        PathNode& currentNode = nodeGrid[(int)currentPos.y][(int)currentPos.x];

        if (currentPos.x == goal.x && currentPos.y == goal.y) {
            auto path = reconstructPath(start, goal, nodeGrid);
            return shouldSmoothPath ? smoothPath(path, isWalkable) : path;
        }

        if (currentNode.closed) continue;
        currentNode.closed = true;

        for (const Vector2& dir : directions) {
            Vector2 neighborPos = {currentPos.x + dir.x, currentPos.y + dir.y};

            // Skip if out of bounds
            if (neighborPos.x < 0 || neighborPos.x >= mapWidth || 
                neighborPos.y < 0 || neighborPos.y >= mapHeight) {
                continue;
            }

            // Skip if not walkable
            if (!isWalkable((int)neighborPos.x, (int)neighborPos.y)) {
                continue;
            }

            PathNode& neighbor = nodeGrid[(int)neighborPos.y][(int)neighborPos.x];
            if (neighbor.closed) continue;

            float movementCost = costFunc(currentPos, neighborPos);
            if (std::abs(dir.x) == 1 && std::abs(dir.y) == 1) {
                movementCost *= 1.414f; // Diagonal cost
            }

            float tentativeG = currentNode.g + movementCost;

            if (tentativeG < neighbor.g) {
                neighbor.parent = currentPos;
                neighbor.g = tentativeG;
                neighbor.h = calculateHeuristic(neighborPos, goal);
                neighbor.f = neighbor.g + neighbor.h;

                if (!neighbor.open) {
                    neighbor.open = true;
                    openSet.push(neighborPos);
                }
            }
        }
    }

    return {}; // No path found
}

} // namespace Pathfinding