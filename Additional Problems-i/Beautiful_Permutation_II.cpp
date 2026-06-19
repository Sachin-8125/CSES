#include <iostream>
#include <vector>
#include <set>
#include <cmath>

using namespace std;

int n;
vector<int> ans;
set<int> avail;

bool dfs(int last_val) {
    if (avail.empty()) return true;
    
    vector<int> cands(avail.begin(), avail.end());
    for (int x : cands) {
        if (abs(x - last_val) > 1) {
            avail.erase(x);
            ans.push_back(x);
            
            if (dfs(x)) return true;
            
            ans.pop_back();
            avail.insert(x);
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n)) return 0;

    if (n == 1) { cout << "1\n"; return 0; }
    if (n == 2 || n == 3) { cout << "NO SOLUTION\n"; return 0; }
    if (n == 4) { cout << "2 4 1 3\n"; return 0; }
    if (n == 5) { cout << "1 3 5 2 4\n"; return 0; }
    if (n == 6) { cout << "1 3 5 2 4 6\n"; return 0; }
    if (n == 7) { cout << "1 3 5 2 6 4 7\n"; return 0; }
    if (n == 8) { cout << "1 3 5 2 6 8 4 7\n"; return 0; }
    if (n == 9) { cout << "1 3 5 2 4 7 9 6 8\n"; return 0; }

    ans.reserve(n);
    ans = {1, 3, 5, 2, 4, 6, 8, 10};
    
    int O_k = 7, E_k = 12;
    bool next_is_odd = true;
    
    while (ans.size() + 15 < n) {
        if (next_is_odd) {
            for (int i = 0; i < 5; i++) ans.push_back(O_k + 2 * i);
            O_k += 10;
        } else {
            for (int i = 0; i < 5; i++) ans.push_back(E_k + 2 * i);
            E_k += 10;
        }
        next_is_odd = !next_is_odd;
    }

    vector<bool> used(n + 1, false);
    for (int x : ans) used[x] = true;
    
    for (int i = 1; i <= n; i++) {
        if (!used[i]) avail.insert(i);
    }

    dfs(ans.back());

    for (int i = 0; i < n; i++) {
        cout << ans[i] << (i == n - 1 ? "" : " ");
    }
    cout << "\n";

    return 0;
}