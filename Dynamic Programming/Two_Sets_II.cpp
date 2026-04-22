#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;

void solve() {
    int n;
    cin >> n;

    int total_sum = n * (n + 1) / 2;

    if (total_sum % 2 != 0) {
        cout << 0 << '\n';
        return;
    }

    int target = total_sum / 2;
    vector<int> dp(target + 1, 0);
    dp[0] = 1;

    for (int num = 1; num < n; num++) {
        for (int sum = target; sum >= num; sum--) {
            dp[sum] = (dp[sum] + dp[sum - num]) % MOD;
        }
    }

    cout << dp[target] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}