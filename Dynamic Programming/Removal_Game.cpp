#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
    int n;
    cin >> n;
    
    vector<long long> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    
    vector<vector<long long>> dp(n, vector<long long>(n, 0));
    
    for (int i = 0; i < n; i++) {
        dp[i][i] = nums[i];
    }
    
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            dp[i][j] = max(nums[i] - dp[i+1][j], nums[j] - dp[i][j-1]);
        }
    }
    
    long long sum = 0;
    for (long long num : nums) {
        sum += num;
    }
    
    long long first_player = (sum + dp[0][n-1]) / 2;
    cout << first_player << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    solve();
    
    return 0;
}