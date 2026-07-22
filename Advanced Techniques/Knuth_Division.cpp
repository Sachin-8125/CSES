#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>

using namespace std;

const long long INF = 1e18;
long long dp[5005][5005];
short opt[5005][5005];
long long sum[5005];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    for (int i = 1; i <= n; ++i) {
        long long x;
        cin >> x;
        sum[i] = sum[i - 1] + x;
        dp[i][i] = 0;
        opt[i][i] = i;
    }

    for (int len = 2; len <= n; ++len) {
        for (int i = 1; i <= n - len + 1; ++i) {
            int j = i + len - 1;
            long long min_cost = INF;
            int best_k = -1;
            int opt_left = opt[i][j - 1];
            int opt_right = opt[i + 1][j];
            
            if (opt_right == j) opt_right--;
            
            for (int k = opt_left; k <= opt_right; ++k) {
                long long cost = dp[i][k] + dp[k + 1][j];
                if (cost < min_cost) {
                    min_cost = cost;
                    best_k = k;
                }
            }
            dp[i][j] = min_cost + sum[j] - sum[i - 1];
            opt[i][j] = best_k;
        }
    }

    cout << dp[1][n] << "\n";

    return 0;
}