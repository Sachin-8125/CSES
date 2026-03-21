#include <bits/stdc++.h>
using namespace std;

unordered_map<int, int> f_cache, s_cache;

int queryF(int idx) {
    if (f_cache.count(idx)) return f_cache[idx];
    cout << "F " << idx << endl;
    cout.flush();
    int score; cin >> score;
    f_cache[idx] = score;
    return score;
}

int queryS(int idx) {
    if (s_cache.count(idx)) return s_cache[idx];
    cout << "S " << idx << endl;
    cout.flush();
    int score; cin >> score;
    s_cache[idx] = score;
    return score;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    
    // Find split: i from Finland, k-i from Sweden
    int lo = max(0, k - n);
    int hi = min(k, n);
    int best_i = lo;
    
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        int j = k - mid;
        
        int f_val = (mid == 0) ? INT_MAX : queryF(mid);
        int s_next = (j >= n) ? INT_MIN : queryS(j + 1);
        
        if (f_val >= s_next) {
            best_i = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    
    int i = best_i, j = k - i;
    int ans;
    
    if (i == 0) {
        ans = queryS(j);
    } else if (j == 0) {
        ans = queryF(i);
    } else {
        ans = min(queryF(i), queryS(j));
    }
    
    cout << "! " << ans << endl;
    
    return 0;
}
