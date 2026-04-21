#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
    int n;
    cin >> n;
    
    vector<int> coins(n);
    for (int i = 0; i < n; i++) {
        cin >> coins[i];
    }
    
    const int MAX_SUM = 100000;
    vector<bool> dp(MAX_SUM + 1, false);
    dp[0] = true;
    
    for (int coin : coins) {
        for (int sum = MAX_SUM; sum >= coin; sum--) {
            if (dp[sum - coin]) {
                dp[sum] = true;
            }
        }
    }
    
    vector<int> res;
    for (int sum = 1; sum <= MAX_SUM; sum++) {
        if (dp[sum]) {
            res.push_back(sum);
        }
    }
    
    cout << res.size() << '\n';
    for (int sum : res) {
        cout << sum << ' ';
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    solve();
    
    return 0;
}