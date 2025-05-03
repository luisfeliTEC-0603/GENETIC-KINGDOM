#ifndef PATHFINDING_HPP
#define PATHFINDING_HPP

#include <vector>
#include <functional>
#include <algorithm>
#include <limits>
#include <cmath>
#include <queue>
#include "raylib.h"
#include "raymath.h"

struct PathNode {
    Vector2 position;
    Vector2 parent;
    float f; // Total cost (g + h)
    float g; // Cost from start
    float h; // Heuristic to goal
    bool closed;
    bool open;

    PathNode();
    PathNode(Vector2 pos);
};

namespace Pathfinding {

    using WalkableCheck = std::function<bool(int x, int y)>;
    using MapDimensions = std::function<void(int& width, int& height)>;
    float calculateHeuristic(Vector2 a, Vector2 b);
    std::vector<Vector2> smoothPath(const std::vector<Vector2>& path, WalkableCheck isWalkable);
    std::vector<Vector2> findPath(
        Vector2 start,
        Vector2 goal,
        WalkableCheck isWalkable,
        MapDimensions getDimensions,
        bool shouldSmoothPath = true
    );
    std::vector<Vector2> findPathWithCost(
        Vector2 start,
        Vector2 goal,
        WalkableCheck isWalkable,
        MapDimensions getDimensions,
        std::function<float(Vector2, Vector2)> costFunc,
        bool shouldSmoothPath = true
    );
}

#endif // PATHFINDING_HPP