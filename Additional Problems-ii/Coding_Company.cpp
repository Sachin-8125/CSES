#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    if (!(cin >> n >> x)) return 0;

    vector<int> t(n);
    for (int i = 0; i < n; ++i) {
        cin >> t[i];
    }

    sort(t.begin(), t.end());

    const int MOD = 1e9 + 7;
    vector<vector<long long>> dp(n + 1, vector<long long>(x + 1, 0));
    dp[0][0] = 1;

    for (int i = 0; i < n; ++i) {
        vector<vector<long long>> next_dp(n + 1, vector<long long>(x + 1, 0));
        int diff = (i == 0) ? 0 : (t[i] - t[i - 1]);

        for (int k = 0; k <= i; ++k) {
            for (int s = 0; s <= x; ++s) {
                if (dp[k][s] == 0) continue;

                long long new_s = s + (long long)k * diff;
                if (new_s > x) continue;

                if (k + 1 <= n) {
                    next_dp[k + 1][new_s] = (next_dp[k + 1][new_s] + dp[k][s]) % MOD;
                }

                next_dp[k][new_s] = (next_dp[k][new_s] + dp[k][s] * (k + 1)) % MOD;

                if (k > 0) {
                    next_dp[k - 1][new_s] = (next_dp[k - 1][new_s] + dp[k][s] * k) % MOD;
                }
            }
        }
        dp = move(next_dp);
    }

    long long total_ways = 0;
    for (int s = 0; s <= x; ++s) {
        total_ways = (total_ways + dp[0][s]) % MOD;
    }

    cout << total_ways << "\n";

    return 0;
}