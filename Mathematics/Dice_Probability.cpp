#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, a, b;
    cin >> n >> a >> b;

    int maxSum = 6 * n;

    vector<long double> dp(maxSum + 1, 0.0L), next_dp(maxSum + 1, 0.0L);

    dp[0] = 1.0L;

    for (int i = 1; i <= n; i++) {
        fill(next_dp.begin(), next_dp.end(), 0.0L);

        for (int s = 0; s <= 6 * (i - 1); s++) {
            if (dp[s] > 0) {
                for (int face = 1; face <= 6; face++) {
                    next_dp[s + face] += dp[s] / 6.0L;
                }
            }
        }

        dp = next_dp;
    }

    long double ans = 0.0L;
    for (int s = a; s <= b && s <= maxSum; s++) {
        ans += dp[s];
    }

    cout << fixed << setprecision(6) << (double)ans << "\n";

    return 0;
}