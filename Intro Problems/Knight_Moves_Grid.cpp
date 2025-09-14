#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<vector<int>> dist(n, vector<int>(n, -1));
    queue<pair<int, int>> q;
    dist[0][0] = 0;
    q.push({0, 0});
    int dr[] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int dc[] = {-1, 1, -2, 2, -2, 2, -1, 1};
    while (!q.empty()) {
        pair<int, int> current = q.front();
        q.pop();
        int r = current.first;
        int c = current.second;
        for (int i = 0; i < 8; ++i) {
            int next_r = r + dr[i];
            int next_c = c + dc[i];
            if (next_r >= 0 && next_r < n && next_c >= 0 && next_c < n && dist[next_r][next_c] == -1) {
                dist[next_r][next_c] = dist[r][c] + 1;
                q.push({next_r, next_c});
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << dist[i][j] << (j == n - 1 ? "" : " ");
        }
        cout << "\n";
    }
    return 0;
}