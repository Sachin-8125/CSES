#include <bits/stdc++.h>
using namespace std;

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, 1, -1};
const char go[] = {'U', 'D', 'R', 'L'};

int nex[1005][1005];

void solve() {
    int n, m;
    cin >> n >> m;

    vector<string> grid(n);
    for (auto& row : grid)
        cin >> row;

    queue<pair<int,int>> q;
    int startX = -1, startY = -1;

    // Multi-source BFS: push all monsters first, then player
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'M') {
                q.push({i, j});
            } else if (grid[i][j] == 'A') {
                startX = i;
                startY = j;
            }
        }
    }

    // Push player last (monsters get processed first = lower priority = closer in BFS)
    q.push({startX, startY});
    nex[startX][startY] = -1;  // player's starting cell has no parent direction

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        // Check if player reached boundary
        if (grid[x][y] == 'A' && (x == 0 || x == n-1 || y == 0 || y == m-1)) {
            // Reconstruct path by backtracking via nex[][]
            string path;
            int d = nex[x][y];
            while (d != -1) {
                path += go[d];
                x -= dx[d];
                y -= dy[d];
                d = nex[x][y];
            }
            reverse(path.begin(), path.end());

            cout << "YES\n";
            cout << path.size() << "\n";
            cout << path << "\n";
            return;
        }

        // Expand neighbors
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if (grid[nx][ny] != '.') continue;  // wall, visited, or monster cell

            // Mark with current cell's type ('M' or 'A')
            grid[nx][ny] = grid[x][y];

            // Only track direction for player cells
            if (grid[nx][ny] == 'A')
                nex[nx][ny] = i;

            q.push({nx, ny});
        }
    }

    cout << "NO\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}