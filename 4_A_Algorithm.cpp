#include <bits/stdc++.h>
using namespace std;


struct Node {
    int x, y;
    int g, h, f;
    Node* parent;
};


struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->f > b->f;
    }
};


int heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

bool isValid(int x, int y, int rows, int cols, vector<vector<int>>& grid) {
    return (x >= 0 && y >= 0 && x < rows && y < cols && grid[x][y] == 0);
}


vector<pair<int,int>> aStarSearch(vector<vector<int>>& grid, pair<int,int> start, pair<int,int> goal) {
    int rows = grid.size();
    int cols = grid[0].size();


    priority_queue<Node*, vector<Node*>, Compare> openList;
  
    vector<vector<bool>> closed(rows, vector<bool>(cols, false));

    Node* startNode = new Node{start.first, start.second, 0, 0, 0, nullptr};
    startNode->h = heuristic(start.first, start.second, goal.first, goal.second);
    startNode->f = startNode->g + startNode->h;

    openList.push(startNode);


    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    while (!openList.empty()) {
        Node* current = openList.top();
        openList.pop();

        int x = current->x;
        int y = current->y;

        if (x == goal.first && y == goal.second) {
          
            vector<pair<int,int>> path;
            while (current != nullptr) {
                path.push_back({current->x, current->y});
                current = current->parent;
            }
            reverse(path.begin(), path.end());
            return path;
        }

        closed[x][y] = true;

      
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (isValid(nx, ny, rows, cols, grid) && !closed[nx][ny]) {
                int gNew = current->g + 1;
                int hNew = heuristic(nx, ny, goal.first, goal.second);
                int fNew = gNew + hNew;

                Node* neighbor = new Node{nx, ny, gNew, hNew, fNew, current};
                openList.push(neighbor);
            }
        }
    }

    return {}; 
}


int main() {
  
    vector<vector<int>> grid = {
        {0, 0, 0, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1},
        {0, 0, 0, 0, 0}
    };

    pair<int,int> start = {0, 0};  
    pair<int,int> goal = {4, 4};  

    vector<pair<int,int>> path = aStarSearch(grid, start, goal);

    if (!path.empty()) {
        cout << "Shortest Path found:\n";
        for (auto p : path) {
            cout << "(" << p.first << "," << p.second << ") ";
        }
        cout << endl;
    } else {
        cout << "No path found!" << endl;
    }

    return 0;
}


