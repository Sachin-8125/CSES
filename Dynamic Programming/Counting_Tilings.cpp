#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;

void generate_transitions(int mask, int i, int next_mask, int n, vector<int>& next_masks) {
    if (i == n) {
        next_masks.push_back(next_mask);
        return;
    }
    
    if (mask & (1 << i)) {
        generate_transitions(mask, i + 1, next_mask, n, next_masks);
    } else {
        generate_transitions(mask, i + 1, next_mask | (1 << i), n, next_masks);
        
        if (i + 1 < n && !(mask & (1 << (i + 1)))) {
            generate_transitions(mask, i + 2, next_mask, n, next_masks);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    if (!(cin >> n >> m)) return 0;
    
    vector<vector<int>> adj(1 << n); 
    for (int mask = 0; mask < (1 << n); ++mask) {
        generate_transitions(mask, 0, 0, n, adj[mask]);
    }
    
    vector<int> dp(1 << n, 0);
    dp[0] = 1;
    
    for (int i = 0; i < m; ++i) {
        vector<int> next_dp(1 << n, 0);
        for (int mask = 0; mask < (1 << n); ++mask) {
            if (!dp[mask]) continue;
            
            for (int next_mask : adj[mask]) {
                next_dp[next_mask] = (next_dp[next_mask] + dp[mask]) % MOD;
            }
        }
        dp = next_dp;
    }
    
    cout << dp[0] << "\n";
    return 0;
}
