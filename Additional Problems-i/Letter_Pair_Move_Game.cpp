#pragma GCC optimize("O3")
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <utility>
#include <numbers> 

using namespace std;

inline void fast_io() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}

constexpr int N = 2e5 + 10;
constexpr double PI = std::numbers::pi; 

unordered_map<string, string> pr; 
vector<string> res;
string s;

unordered_map<int, string> dp; 

void precompute(int n) {
    int sz = 0;
    for (int i = 0; i <= n - 2; ++i) {
        string cur = string(i, 'A') + string(n - 2 - i, 'B');
        cur.insert(0, "..");
        dp[sz++] = cur;
        pr[cur] = "";
        
        if (n < 8) {
            cur = string(i, 'A') + string(n - 2 - i, 'B');
            cur.insert(1, "..");
            dp[sz++] = cur;
            pr[cur] = "";
        }
    }
    
    int i = 0;
    while (i < sz) {
        string cur = dp[i++];
        size_t k = cur.find('.');
        for (int j = 0; j < n - 1; ++j) {
            if (cur[j] != '.' && cur[j + 1] != '.') {
                string nxt = cur;
                swap(nxt[j], nxt[k]);
                swap(nxt[j + 1], nxt[k + 1]);
                
                if (!pr.contains(nxt)) {
                    pr[nxt] = cur;
                    dp[sz++] = nxt;
                }
            }
        }
    }
}

void solve(int l, int r) {
    string cur = s.substr(l, r - l);
    while (!pr[cur].empty()) {
        cur = pr[cur];
        res.push_back(s.substr(0, l) + cur + s.substr(r));
    }
    s = s.substr(0, l) + cur + s.substr(r);
}

void op(int i, int j) {
    swap(s[i], s[j]);
    swap(s[i + 1], s[j + 1]);
    res.push_back(s);
}

int main() {
    fast_io();
    
    int n;
    if (!(cin >> n)) return 0;
    
    if (n == 1) {
        cout << 0 << '\n';
        return 0;
    }
    
    cin >> s;
    if (n * 2 < 8) {
        precompute(n * 2);
        if (!pr.contains(s)) {
            cout << "-1\n";
            return 0;
        }
        solve(0, n * 2);
    } else {
        size_t dots_pos = s.find('.');
        if (dots_pos > 1) {
            op(dots_pos, 0);
        } else if (dots_pos == 1) {
            op(dots_pos, 3);
            op(3, 0);
        }
        
        dots_pos = 0;
        precompute(8);
        
        while (dots_pos + 8 < static_cast<size_t>(2 * n)) {
            if (s[dots_pos + 2] == 'A' && s[dots_pos + 3] == 'A') {
                op(dots_pos, dots_pos + 2);
                dots_pos += 2;
            } else {
                size_t b_pos = s.find('B', dots_pos);
                size_t a_pos = s.find('A', b_pos + 2);
                bool flag = false;
                
                if (a_pos == string::npos) {
                    solve(dots_pos, dots_pos + 8);
                    break;
                } else if (a_pos == static_cast<size_t>(2 * n - 1)) {
                    --a_pos;
                    flag = true;
                }
                
                op(dots_pos, b_pos);
                op(b_pos, a_pos);
                op(a_pos, dots_pos);
                
                if (flag) {
                    solve(dots_pos, dots_pos + 8);
                }
            }
        }
        solve(dots_pos, dots_pos + 8);
    }
    
    cout << res.size() << '\n';
    for (const auto& x : res) {
        cout << x << '\n';
    }
    
    return 0;
}
