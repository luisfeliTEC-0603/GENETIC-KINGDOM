#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;

// Node structure definition
struct Node {
    int x, y;
    float g, h;
    Node* parent;

    Node(int x, int y, float g, float h, Node* parent = nullptr)
        : x(x), y(y), g(g), h(h), parent(parent) {}

    float f() const { return g + h; }
};

// Comparator for priority_queue (smallest f() first)
struct CompareNode {
    bool operator()(const Node* a, const Node* b) const {
        return a->f() > b->f();
    }
};

// Manhattan distance heuristic
float heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

// Check if a position is within the grid and not an obstacle
bool isValid(int x, int y, const vector<vector<int>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    return (x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == 0);
}

// Reconstructs the path from the destination node to the start node
void reconstructPath(Node* endNode) {
    vector<pair<int, int>> path;
    Node* current = endNode;
    while (current != nullptr) {
        path.push_back({current->x, current->y});
        current = current->parent;
    }

    reverse(path.begin(), path.end());

    cout << "Path found:" << endl;
    for (auto [x, y] : path) {
        cout << "(" << x << ", " << y << ")" << endl;
    }
}

// A* search implementation
void aStar(const vector<vector<int>>& grid, pair<int, int> start, pair<int, int> goal) {
    priority_queue<Node*, vector<Node*>, CompareNode> openList;
    vector<vector<bool>> closed(grid.size(), vector<bool>(grid[0].size(), false));

    Node* startNode = new Node(start.first, start.second, 0, heuristic(start.first, start.second, goal.first, goal.second));
    openList.push(startNode);

    // Possible moves: up, down, left, right
    vector<pair<int, int>> directions = {{-1,0},{1,0},{0,-1},{0,1}};

    while (!openList.empty()) {
        Node* current = openList.top();
        openList.pop();

        if (current->x == goal.first && current->y == goal.second) {
            reconstructPath(current);
            return;
        }

        closed[current->x][current->y] = true;

        for (auto [dx, dy] : directions) {
            int nx = current->x + dx;
            int ny = current->y + dy;

            if (isValid(nx, ny, grid) && !closed[nx][ny]) {
                float gCost = current->g + 1;
                float hCost = heuristic(nx, ny, goal.first, goal.second);
                Node* neighbor = new Node(nx, ny, gCost, hCost, current);
                openList.push(neighbor);
            }
        }
    }

    cout << "No path found." << endl;
}

int main() {
    // 0 = open, 1 = obstacle
    vector<vector<int>> grid = {
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0}
    };

    pair<int, int> start = {0, 0};
    pair<int, int> goal = {4, 4};

    aStar(grid, start, goal);

    return 0;
}
