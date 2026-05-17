#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<tuple<int, int, long long>> projects;
    for (int i = 0; i < n; i++) {
        int a, b;
        long long p;
        cin >> a >> b >> p;
        projects.emplace_back(b, a, p);
    }
    
    sort(projects.begin(), projects.end());
    
    vector<long long> dp(n + 1, 0);
    
    for (int i = 0; i < n; i++) {
        int start = get<1>(projects[i]);
        int end = get<0>(projects[i]);
        long long reward = get<2>(projects[i]);
        
        int lo = 0, hi = i - 1, idx = -1;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (get<0>(projects[mid]) < start) {
                idx = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        
        dp[i + 1] = max(dp[i], (idx == -1 ? 0 : dp[idx + 1]) + reward);
    }
    
    cout << dp[n] << '\n';
    
    return 0;
}
