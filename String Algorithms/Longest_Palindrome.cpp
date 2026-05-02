#include<bits/stdc++.h>
using namespace std;
#define int long long
#define IOS ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);

string manacher(string s) {
    if (s.empty()) return "";
    
    string t = "^#";
    for (char c : s) {
        t += string(1, c) + "#";
    }
    t += "$";
    
    int n = t.size();
    vector<int> P(n, 0); 
    
    int center = 0, right = 0;  
    
    int maxLen = 0;
    int maxCenter = 0;
    
    for (int i = 1; i < n - 1; i++) {
        int mirror = 2 * center - i;
        
        if (i < right) {
            P[i] = min(right - i, P[mirror]);
        }
        
        while (t[i + (P[i] + 1)] == t[i - (P[i] + 1)]) {
            P[i]++;
        }
        
        if (i + P[i] > right) {
            center = i;
            right = i + P[i];
        }
        
        if (P[i] > maxLen) {
            maxLen = P[i];
            maxCenter = i;
        }
    }
    
    int start = (maxCenter - maxLen) / 2;
    return s.substr(start, maxLen);
}

void solve(){
    string s;
    cin >> s;
    cout << manacher(s);
}

signed main(){
    IOS;
    solve();
}
