#include "aStar.hpp"

AStarNode::AStarNode(Vector2 pos, float g, float h, AStarNode* parent)
    : position(pos), g(g), h(h), parent(parent) {}

float AStarNode::getF() const { return g + h; }

bool AStarNodeComparator::operator()(const AStarNode* a, const AStarNode* b) const {
    return a->getF() > b->getF();
}

float AStarPathfinder::calculateHeuristic(const Vector2& a, const Vector2& b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

bool AStarPathfinder::isPositionValid(const Vector2& pos, const std::vector<std::vector<int>>& grid) {    
    if (pos.y < 0 || pos.y >= static_cast<int>(grid.size()) || 
        pos.x < 0 || pos.x >= static_cast<int>(grid[0].size())) {
        return false;
    }
    
    static const std::unordered_set<int> validValues = {0, 4, 2};
    return validValues.count(grid[pos.y][pos.x]) > 0;
}

std::vector<Vector2> AStarPathfinder::findPath(
    const std::vector<std::vector<int>>& grid,
    const Vector2& start,
    const Vector2& goal
) {

    if (!isPositionValid(start, grid)) {
        return {};
    }
    if (!isPositionValid(goal, grid)) {

        return {};
    }

    std::priority_queue<AStarNode*, std::vector<AStarNode*>, AStarNodeComparator> openList;
    std::vector<std::vector<bool>> closed(
        grid.size(), 
        std::vector<bool>(grid.empty() ? 0 : grid[0].size(), false)
    );
    std::vector<std::unique_ptr<AStarNode>> nodesToDelete;

    nodesToDelete.emplace_back(new AStarNode(start, 0, calculateHeuristic(start, goal)));
    openList.push(nodesToDelete.back().get());

    const std::vector<Vector2> directions = {{-1,0},{1,0},{0,-1},{0,1}};

    while (!openList.empty()) {
        AStarNode* current = openList.top();
        openList.pop();

        if (current->position.x == goal.x && current->position.y == goal.y) {
            std::vector<Vector2> path;
            AStarNode* node = current;
            while (node != nullptr) {
                path.push_back(node->position);
                node = node->parent;
            }
            std::reverse(path.begin(), path.end());
            
            return path;
        }

        closed[current->position.y][current->position.x] = true;

        for (const auto& dir : directions) {
            Vector2 neighborPos = { 
                current->position.x + dir.x, 
                current->position.y + dir.y 
            };

            if (isPositionValid(neighborPos, grid)) {
                if (!closed[neighborPos.y][neighborPos.x]) {
                    float gCost = current->g + 1;
                    float hCost = calculateHeuristic(neighborPos, goal);
                    
                    nodesToDelete.emplace_back(new AStarNode(neighborPos, gCost, hCost, current));
                    openList.push(nodesToDelete.back().get());
                } 
            }
        }
    }

    return {};
}