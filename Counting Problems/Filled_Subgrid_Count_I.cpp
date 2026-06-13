#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

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

    vector<int> dp(n, 0);
    vector<long long> counts(26, 0);

    for (int i = 0; i < n; ++i) {
        int prev_dp = 0;
        for (int j = 0; j < n; ++j) {
            int temp = dp[j];
            
            if (i == 0 || j == 0) {
                dp[j] = 1;
            } else {
                char c = grid[i][j];
                if (grid[i-1][j] == c && grid[i][j-1] == c && grid[i-1][j-1] == c) {
                    dp[j] = 1 + min({dp[j], dp[j-1], prev_dp});
                } else {
                    dp[j] = 1;
                }
            }
            
            counts[grid[i][j] - 'A'] += dp[j];
            prev_dp = temp; 
        }
    }

    for (int i = 0; i < k; ++i) {
        cout << counts[i] << "\n";
    }

    return 0;
}