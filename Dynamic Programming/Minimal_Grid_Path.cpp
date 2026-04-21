#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<string> grid(n);
    for (int i = 0; i < n; ++i) cin >> grid[i];

    string result = "";
    result += grid[0][0];

    // current_layer stores coordinates reached at the current step
    vector<pair<int, int>> current_layer;
    current_layer.push_back({0, 0});
    
    // visited array to avoid redundant processing in O(n^2)
    vector<vector<bool>> visited(n, vector<bool>(n, false));

    for (int step = 0; step < 2 * n - 2; ++step) {
        char min_char = 'Z' + 1;
        vector<pair<int, int>> next_layer_candidates;

        for (auto& [r,c] : current_layer) {
            int dr[] = {0, 1};
            int dc[] = {1, 0};

            for (int i = 0; i < 2; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];

                if (nr < n && nc < n && !visited[nr][nc]) {
                    if (grid[nr][nc] < min_char) {
                        min_char = grid[nr][nc];
                    }
                    visited[nr][nc] = true;
                    next_layer_candidates.push_back({nr, nc});
                }
            }
        }

        result += min_char;
        current_layer.clear();
        
        // Pruning: only carry forward coordinates that match the minimum char
        for (auto& [r,c] : next_layer_candidates) {
            if (grid[r][c] == min_char) {
                current_layer.push_back({r, c});
            }
        }
    }

    cout << result << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}