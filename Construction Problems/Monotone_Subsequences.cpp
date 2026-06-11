#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    
    if (n > (long long)k * k) {
        cout << "IMPOSSIBLE\n";
        return;
    }
    
    vector<int> ans;
    int curr = 1;
    
    while (curr <= n) {
        int sz = min(k, n - curr + 1);
        
        vector<int> block;
        for (int i = 0; i < sz; ++i) {
            block.push_back(curr++);
        }
        
        reverse(block.begin(), block.end());
        
        for (int x : block) {
            ans.push_back(x);
        }
    }
    
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << (i == n - 1 ? "" : " ");
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    
    return 0;
}