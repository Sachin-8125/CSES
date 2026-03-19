#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, a, b;
    if (!(cin >> n >> a >> b)) return 0;
    
    vector<long long> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    
    // Prefix sums
    vector<long long> pref(n + 1, 0);
    for (int i = 0; i < n; i++) pref[i + 1] = pref[i] + arr[i];
    
    deque<int> dq;
    long long ans = LLONG_MIN;
    
    for (int i = a; i <= n; i++) {
        while (!dq.empty() && pref[dq.back()] >= pref[i - a]) {
            dq.pop_back();
        }
        dq.push_back(i - a);
        while (!dq.empty() && dq.front() < i - b) {
            dq.pop_front();
        }
        ans = max(ans, pref[i] - pref[dq.front()]);
    }
    cout << ans << "\n";
    return 0;
}