#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int MAXK = 125002; 
long long dp[MAXK], old_dp[MAXK];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    dp[0] = 1;

    for (int i = 2; i <= n; i++) {
        memcpy(old_dp, dp, sizeof(long long) * (k + 1));
        for (int j = 0; j <= k; j++) {
            dp[j] = (j > 0 ? dp[j-1] : 0LL)
                  + old_dp[j]
                  + MOD                             
                  - (j >= i ? old_dp[j - i] : 0LL);
            dp[j] %= MOD;
        }
    }

    cout << dp[k] << "\n";
    return 0;
}