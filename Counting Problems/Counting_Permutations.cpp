#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    long long MOD = 1e9 + 7;
    vector<vector<long long>> dp(n + 2, vector<long long>(2, 0));
    dp[0][0] = 1;

    for (int i = 2; i <= n; ++i) {
        vector<vector<long long>> next_dp(n + 2, vector<long long>(2, 0));
        for (int j = 0; j <= i; ++j) {
            for (int k = 0; k < 2; ++k) {
                long long val = dp[j][k];
                if (val == 0) continue;

                if (k == 0) {
                    next_dp[j + 1][1] = (next_dp[j + 1][1] + val * 2) % MOD;
                    if (j > 0) {
                        next_dp[j - 1][0] = (next_dp[j - 1][0] + val * j) % MOD;
                    }
                    if (i - 2 - j > 0) {
                        next_dp[j][0] = (next_dp[j][0] + val * (i - 2 - j)) % MOD;
                    }
                } else {
                    next_dp[j][1] = (next_dp[j][1] + val) % MOD;
                    next_dp[j + 1][1] = (next_dp[j + 1][1] + val) % MOD;
                    if (j > 1) {
                        next_dp[j - 1][0] = (next_dp[j - 1][0] + val * (j - 1)) % MOD;
                    }
                    if (i - j - 1 > 0) {
                        next_dp[j][0] = (next_dp[j][0] + val * (i - j - 1)) % MOD;
                    }
                }
            }
        }
        dp = move(next_dp);
    }

    cout << dp[0][0] << "\n";
    return 0;
}