#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;
    vector<int> x(n);
    for (int i = 0; i < n; ++i) cin >> x[i];

    vector<int> dp(m + 2, 0), ndp(m + 2, 0);

    // base case for i = 0 (1st position, index 0)
    if (x[0] == 0) {
        for (int v = 1; v <= m; ++v) {
            dp[v] = 1;
        }
    } else {
        dp[x[0]] = 1;
    }

    for (int i = 1; i < n; ++i) {
        fill(ndp.begin(), ndp.end(), 0);

        if (x[i] == 0) {
            for (int v = 1; v <= m; ++v) {
                long long res = dp[v];
                if (v - 1 >= 1) res += dp[v - 1];
                if (v + 1 <= m) res += dp[v + 1];
                ndp[v] = res % MOD;
            }
        } else {
            int v = x[i];
            long long res = dp[v];
            if (v - 1 >= 1) res += dp[v - 1];
            if (v + 1 <= m) res += dp[v + 1];
            ndp[v] = res % MOD;
            // others stay 0
        }

        dp.swap(ndp);
    }

    long long ans = 0;
    for (int v = 1; v <= m; ++v) {
        ans += dp[v];
        if (ans >= MOD) ans -= MOD;
    }

    cout << ans % MOD << '\n';
    return 0;
}
