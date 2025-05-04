/** 
 *  @file Sources/Game/Pathfinding/aStar.hpp
 *  @brief A* Pathfinding algorithm implementation for grid-based navigation
 */

#ifndef A_STAR_HPP
#define A_STAR_HPP

#include <vector>
#include <memory>
#include <queue>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <unordered_set>

#include "raylib.h"
#include "raymath.h"

/**
 * @struct AStarNode
 * @brief Represents a node in the A* pathfinding graph
 * 
 * @param postion ; (x, y) coordinates in grid
 * @param g : cost from start to current node
 * @param h : heuristic cost from current to end
 * @param parent : pointer to parent node (for path reconstruction) (default = nullptr)
 * 
 * @def getF()
 * @return total estimated cost of path through this node
 */

struct AStarNode {
    Vector2 position;
    float g;
    float h;
    AStarNode* parent;

    AStarNode(Vector2 pos, float g, float h, AStarNode* parent = nullptr);
    float getF() const;
};

/**
 * @struct AStarNodeComparator
 * @brief functor for comparing node priorities in the open set
 * 
 * @param a first node to compare
 * @param b second node to compare
 * 
 * @return true if a's F cost is greater than b's
 */

struct AStarNodeComparator {
    bool operator()(const AStarNode* a, const AStarNode* b) const;
};

/**
 * @class AStarPathfinder
 * @brief Implementation of the A* pathfinding algorithm
 * 
 * @public findPath : finds the optimal path from start to goal on a grid
 * @param grid 2D grid
 * @param start starting position in grid coordinates
 * @param goal target position in grid coordinates
 * @return vector of positions representing the path (empty if no path found)
 * @note The returned path includes both start and end positions
 * @warning Grid coordinates must be integers
 * 
 * @private calculateHeuristic
 * @param a First position
 * @param b Second position
 * @return euclidean distance -> sqrt(dx² + dy²)
 * 
 * @private isPositionValid
 * @param pos Position to check
 * @param grid Reference to the game grid
 * @return True if position is within bounds and not blocked
 */

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