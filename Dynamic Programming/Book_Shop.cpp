#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, x;
    cin >> n >> x;
    
    vector<int> price(n), pages(n);
    
    for (int i = 0; i < n; i++) {
        cin >> price[i];
    }
    
    for (int i = 0; i < n; i++) {
        cin >> pages[i];
    }
    
    // dp[i] = maximum pages we can get with budget i
    vector<int> dp(x + 1, 0);
    
    // For each book
    for (int i = 0; i < n; i++) {
        // Iterate backwards to avoid using same book multiple times
        for (int j = x; j >= price[i]; j--) {
            dp[j] = max(dp[j], dp[j - price[i]] + pages[i]);
        }
    }
    
    // The answer is the maximum pages with any budget <= x
    cout << dp[x] << endl;
    
    return 0;
}
