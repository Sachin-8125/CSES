#include <iostream>
#include <vector>

using namespace std;

const long long MOD = 1e9 + 7;
const int MAX_N = 1e6 + 6;

void precomputeDP(vector<vector<long long>>& dp) {
    dp[1][1] = dp[1][2] = 1;
    
    for (int i = 2; i < MAX_N; i++) {
        dp[i][1] = (4LL * dp[i-1][1] % MOD + dp[i-1][2]) % MOD;
        dp[i][2] = (dp[i-1][1] + 2LL * dp[i-1][2] % MOD) % MOD;
    }
}

long long solve(int n, const vector<vector<long long>>& dp) {
    return (dp[n][1] + dp[n][2]) % MOD;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    vector<vector<long long>> dp(MAX_N, vector<long long>(3, 0));
    precomputeDP(dp);
    
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        cout << solve(n, dp) << '\n';
    }
    
    return 0;
}