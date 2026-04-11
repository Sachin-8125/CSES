#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    const int INF = 1e9;
    vector<int> dp(n + 1, INF);
    dp[0] = 0;

    for (int i = 1; i <= n; ++i) {
        int x = i;
        while (x > 0) {
            int d = x % 10;
            if (d != 0) {                    // optional, 0 does nothing
                dp[i] = min(dp[i], 1 + dp[i - d]);
            }
            x /= 10;
        }
    }

    cout << dp[n] << '\n';
    return 0;
}
