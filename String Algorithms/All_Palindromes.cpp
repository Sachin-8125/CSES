#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    cin >> s;
    int n = s.size();
    
    vector<int> d1(n), d2(n);
    
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
        while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) k++;
        d1[i] = k--;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }
    
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
        while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) k++;
        d2[i] = k--;
        if (i + k > r) {
            l = i - k - 1;
            r = i + k;
        }
    }
    
    vector<int> ans(n, 1); 

    // Odd-length palindromes: center c covers end positions [c, c + d1[c] - 1]
    int p = 0;
    for (int e = 0; e < n; e++) {
        while (p <= e && p + d1[p] - 1 < e) p++;
        if (p <= e) {
            ans[e] = max(ans[e], 2 * (e - p) + 1);
        }
    }
    
    // Even-length palindromes: center c covers end positions [c, c + d2[c] - 1]
    p = 0;
    for (int e = 0; e < n; e++) {
        while (p <= e && (d2[p] == 0 || p + d2[p] - 1 < e)) p++;
        if (p <= e && d2[p] > 0) {
            ans[e] = max(ans[e], 2 * (e - p + 1));
        }
    }
    
    for (int i = 0; i < n; i++) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    
    return 0;
}