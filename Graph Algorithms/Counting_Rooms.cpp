#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<string> grid;
vector<vector<bool>> visited;

// Directions: right, left, down, up
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

void dfs(int x, int y) {
    visited[x][y] = true;
    for (int dir = 0; dir < 4; ++dir) {
        int nx = x + dx[dir];
        int ny = y + dy[dir];
        if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
            if (!visited[nx][ny] && grid[nx][ny] == '.')
                dfs(nx, ny);
        }
    }
}

int main() {
    cin >> n >> m;
    grid.resize(n);
    visited.assign(n, vector<bool>(m, false));
    for (int i = 0; i < n; ++i) {
        cin >> grid[i];
    }
    int rooms = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == '.' && !visited[i][j]) {
                dfs(i, j);
                ++rooms;
            }
        }
    }
    cout << rooms << endl;
    return 0;
}
