#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<int>> cnt(n, vector<int>(n, 0));
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        cnt[a][b]++;
    }

    int full = (1 << n) - 1;
    vector<vector<int>> dp(1 << n, vector<int>(n, 0));
    dp[1][0] = 1;

    for (int mask = 1; mask <= full; mask++) {
        if (!(mask & 1)) continue;
        for (int i = 0; i < n; i++) {
            if (!(mask & (1 << i)) || dp[mask][i] == 0) continue;
            if (i == n - 1 && mask != full) continue;
            for (int j = 0; j < n; j++) {
                if ((mask & (1 << j)) || cnt[i][j] == 0) continue;
                int& ref = dp[mask | (1 << j)][j];
                ref = (ref + (long long)dp[mask][i] * cnt[i][j]) % MOD;
            }
        }
    }

    cout << dp[full][n - 1] << "\n";

    return 0;
}
