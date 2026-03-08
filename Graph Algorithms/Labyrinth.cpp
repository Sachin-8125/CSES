#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<string> g(n);
    for (int i = 0; i < n; ++i) cin >> g[i];

    pair<int,int> s{-1,-1}, t{-1,-1};
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            if (g[i][j] == 'A') s = {i, j};
            if (g[i][j] == 'B') t = {i, j};
        }

    const string dirs = "UDLR";
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    vector<vector<bool>> vis(n, vector<bool>(m, false));
    vector<vector<char>> from(n, vector<char>(m, 0));

    queue<pair<int,int>> q;
    q.push(s);
    vis[s.first][s.second] = true;

    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        if (x == t.first && y == t.second) break;

        for (int k = 0; k < 4; ++k) {
            int nx = x + dx[k], ny = y + dy[k];
            if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
            if (vis[nx][ny] || g[nx][ny] == '#') continue;
            vis[nx][ny] = true;
            from[nx][ny] = dirs[k];
            q.push({nx, ny});
        }
    }

    if (!vis[t.first][t.second]) {
        cout << "NO\n";
        return 0;
    }

    string path;
    int x = t.first, y = t.second;
    while (x != s.first || y != s.second) {
        char c = from[x][y];
        path.push_back(c);
        if (c == 'U') x += 1;
        else if (c == 'D') x -= 1;
        else if (c == 'L') y += 1;
        else if (c == 'R') y -= 1;
    }
    reverse(path.begin(), path.end());

    cout << "YES\n";
    cout << path.size() << '\n';
    cout << path << '\n';
}

