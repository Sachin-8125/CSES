#include <iostream>
#include <vector>
#include <string>

using namespace std;

int n;
vector<vector<int>> adj;
vector<int> matchL, matchR;
vector<bool> visR, Z_L, Z_R;

bool dfs(int u) {
    for (int v : adj[u]) {
        if (visR[v]) continue;
        visR[v] = true;
        if (matchR[v] == -1 || dfs(matchR[v])) {
            matchL[u] = v;
            matchR[v] = u;
            return true;
        }
    }
    return false;
}

void dfs_cover(int u) {
    Z_L[u] = true;
    for (int v : adj[u]) {
        if (!Z_R[v]) {
            Z_R[v] = true;
            if (matchR[v] != -1 && !Z_L[matchR[v]]) {
                dfs_cover(matchR[v]);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n)) return 0;

    adj.resize(n + 1);
    matchL.assign(n + 1, -1);
    matchR.assign(n + 1, -1);

    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < n; j++) {
            if (s[j] == 'o') {
                adj[i].push_back(j + 1);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        visR.assign(n + 1, false);
        dfs(i);
    }

    Z_L.assign(n + 1, false);
    Z_R.assign(n + 1, false);

    for (int i = 1; i <= n; i++) {
        if (matchL[i] == -1) {
            dfs_cover(i);
        }
    }

    vector<pair<int, int>> ans;
    for (int i = 1; i <= n; i++) {
        if (!Z_L[i]) ans.push_back({1, i});
    }
    for (int j = 1; j <= n; j++) {
        if (Z_R[j]) ans.push_back({2, j});
    }

    cout << ans.size() << "\n";
    for (auto p : ans) {
        cout << p.first << " " << p.second << "\n";
    }

    return 0;
}