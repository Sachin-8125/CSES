#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<long long> dp(n + 1, 0);
    dp[1] = 1;

    for (int i = 2; i <= n; ++i) {
        vector<long long> next_dp(n + 1, 0);
        for (int k = 1; k <= i; ++k) {
            next_dp[k] = (k * dp[k] % MOD + (i - k + 1) * dp[k - 1] % MOD) % MOD;
        }
        dp = move(next_dp);
    }

    for (int k = 1; k <= n; ++k) {
        cout << dp[k] << endl;
    }
    cout << "\n";

    return 0;
}