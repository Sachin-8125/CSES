#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int a, b;
    cin >> a >> b;

    vector<vector<int>> dp(a + 1, vector<int>(b + 1));

    for (int i = 1; i <= a; i++) {
        for (int j = 1; j <= b; j++) {
            if (i == j) {
                dp[i][j] = 0;
                continue;
            }
            
            int min_cuts = 1e9;

            // Horizontal cuts
            for (int k = 1; k < i; k++) {
                min_cuts = min(min_cuts, 1 + dp[k][j] + dp[i - k][j]);
            }

            // Vertical cuts
            for (int k = 1; k < j; k++) {
                min_cuts = min(min_cuts, 1 + dp[i][k] + dp[i][j - k]);
            }

            dp[i][j] = min_cuts;
        }
    }

    cout << dp[a][b] << endl;

    return 0;
}