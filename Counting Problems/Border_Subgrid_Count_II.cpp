#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<string> grid(n);
    for (int i = 0; i < n; ++i) {
        cin >> grid[i];
    }

    vector<vector<int>> up(n, vector<int>(n));
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < n; ++i) {
            if (i == 0 || grid[i][j] != grid[i - 1][j]) {
                up[i][j] = 1;
            } else {
                up[i][j] = up[i - 1][j] + 1;
            }
        }
    }

    vector<long long> ans(26, 0);

    for (int r1 = 0; r1 < n; ++r1) {
        for (int r2 = r1; r2 < n; ++r2) {
            int active_L = -1;
            int current_count = 0;
            int h = r2 - r1 + 1;
            for (int c = 0; c < n; ++c) {
                int L1 = grid[r1][c] - 'A';
                int L2 = grid[r2][c] - 'A';
                
                int L = (L1 == L2) ? L1 : -1;
                
                if (L != -1 && L == active_L) {
                    if (up[r2][c] >= h) {
                        ans[L] += current_count + 1;
                        current_count++;
                    }
                } else {
                    active_L = L;
                    current_count = 0;
                    if (L != -1) {
                        if (up[r2][c] >= h) {
                            ans[L] += 1;
                            current_count = 1;
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < k; ++i) {
        cout << ans[i] << "\n";
    }

    return 0;
}