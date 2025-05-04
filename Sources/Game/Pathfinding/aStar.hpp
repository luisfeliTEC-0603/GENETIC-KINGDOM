#ifndef A_STAR_HPP
#define A_STAR_HPP

#include <vector>
#include <memory>
#include <queue>
#include <algorithm>
#include <cmath>
#include <iostream>

#include "raylib.h"
#include "raymath.h"

struct AStarNode {
    Vector2 position;
    float g;  // Cost from start to current node
    float h;  // Heuristic cost from current to end
    AStarNode* parent;

    AStarNode(Vector2 pos, float g, float h, AStarNode* parent = nullptr);
    float getF() const;
};

struct AStarNodeComparator {
    bool operator()(const AStarNode* a, const AStarNode* b) const;
};

class AStarPathfinder {
public:
    static std::vector<Vector2> findPath(
        const std::vector<std::vector<int>>& grid,
        const Vector2& start,
        const Vector2& goal
    );

private:
    static float calculateHeuristic(const Vector2& a, const Vector2& b);
    static bool isPositionValid(const Vector2& pos, const std::vector<std::vector<int>>& grid);
};

#endif // A_STAR_HPP