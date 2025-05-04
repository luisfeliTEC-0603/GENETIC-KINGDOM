#include "aStar.hpp"

AStarNode::AStarNode(Vector2 pos, float g, float h, AStarNode* parent)
    : position(pos), g(g), h(h), parent(parent) {}

float AStarNode::getF() const {
    return g + h;
}

bool AStarNodeComparator::operator()(const AStarNode* a, const AStarNode* b) const {
    return a->getF() > b->getF();
}

float AStarPathfinder::calculateHeuristic(const Vector2& a, const Vector2& b) {
    // Manhattan distance
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

bool AStarPathfinder::isPositionValid(const Vector2& pos, const std::vector<std::vector<int>>& grid) {
    // Debug: Print position being checked
    std::cout << "Checking position: (" << pos.x << ", " << pos.y << ")\n";
    
    // Check bounds (note: grid[y][x] is the conventional order)
    if (pos.y < 0 || pos.y >= static_cast<int>(grid.size()) || 
        pos.x < 0 || pos.x >= static_cast<int>(grid[0].size())) {
        std::cout << "Position out of bounds\n";
        return false;
    }
    
    // Check if walkable (0 means walkable in this convention)
    bool valid = (grid[pos.y][pos.x] == 0) || (grid[pos.y][pos.x] == 4) || (grid[pos.y][pos.x] == 2) ;
    std::cout << "Position valid: " << std::boolalpha << valid << "\n";
    return valid;
}

std::vector<Vector2> AStarPathfinder::findPath(
    const std::vector<std::vector<int>>& grid,
    const Vector2& start,
    const Vector2& goal
) {
    // Debug: Print start and goal
    std::cout << "\n===== A* Pathfinding =====\n";
    std::cout << "Start: (" << start.x << ", " << start.y << ")\n";
    std::cout << "Goal: (" << goal.x << ", " << goal.y << ")\n";
    std::cout << "Grid size: " << grid.size() << " rows x " 
              << (grid.empty() ? 0 : grid[0].size()) << " columns\n";

    // Validate start and goal positions
    if (!isPositionValid(start, grid)) {
        std::cerr << "ERROR: Start position is invalid!\n";
        return {};
    }
    if (!isPositionValid(goal, grid)) {
        std::cerr << "ERROR: Goal position is invalid!\n";
        return {};
    }

    std::priority_queue<AStarNode*, std::vector<AStarNode*>, AStarNodeComparator> openList;
    std::vector<std::vector<bool>> closed(
        grid.size(), 
        std::vector<bool>(grid.empty() ? 0 : grid[0].size(), false)
    );
    std::vector<std::unique_ptr<AStarNode>> nodesToDelete;

    // Debug: Print initial node creation
    std::cout << "Creating initial node...\n";
    nodesToDelete.emplace_back(new AStarNode(start, 0, calculateHeuristic(start, goal)));
    openList.push(nodesToDelete.back().get());

    const std::vector<Vector2> directions = {{-1,0},{1,0},{0,-1},{0,1}};
    int iteration = 0;

    while (!openList.empty()) {
        iteration++;
        AStarNode* current = openList.top();
        openList.pop();

        // Debug: Print current node being processed
        std::cout << "\nIteration " << iteration << ": Processing node at (" 
                  << current->position.x << ", " << current->position.y << ")\n";
        std::cout << "g=" << current->g << ", h=" << current->h << ", f=" << current->getF() << "\n";

        // Check if we've reached the goal
        if (current->position.x == goal.x && current->position.y == goal.y) {
            std::cout << "Goal reached! Reconstructing path...\n";
            std::vector<Vector2> path;
            AStarNode* node = current;
            while (node != nullptr) {
                path.push_back(node->position);
                node = node->parent;
            }
            std::reverse(path.begin(), path.end());
            
            // Debug: Print final path
            std::cout << "Path found with " << path.size() << " points:\n";
            for (const auto& p : path) {
                std::cout << "(" << p.x << ", " << p.y << ") ";
            }
            std::cout << "\n";
            
            return path;
        }

        if (closed[current->position.y][current->position.x]) {
            std::cout << "Node already closed, skipping\n";
            continue;
        }
        closed[current->position.y][current->position.x] = true;

        // Explore neighbors
        for (const auto& dir : directions) {
            Vector2 neighborPos = { 
                current->position.x + dir.x, 
                current->position.y + dir.y 
            };

            std::cout << "Checking neighbor at (" << neighborPos.x << ", " << neighborPos.y << ")\n";

            if (isPositionValid(neighborPos, grid)) {
                if (!closed[neighborPos.y][neighborPos.x]) {
                    float gCost = current->g + 1;
                    float hCost = calculateHeuristic(neighborPos, goal);
                    
                    // Debug: Print neighbor info
                    std::cout << "Adding neighbor to open list: g=" << gCost 
                              << ", h=" << hCost << "\n";
                    
                    nodesToDelete.emplace_back(new AStarNode(neighborPos, gCost, hCost, current));
                    openList.push(nodesToDelete.back().get());
                } else {
                    std::cout << "Neighbor already closed\n";
                }
            }
        }
    }

    std::cout << "No path found to goal!\n";
    return {};
}