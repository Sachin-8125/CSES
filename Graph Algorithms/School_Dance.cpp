#include <iostream>
#include <vector>

using namespace std;

int n, m, k;
vector<vector<int>> adj;
vector<int> match;
vector<bool> vis;

bool dfs(int u) {
    for (int v : adj[u]) {
        if (vis[v]) continue;
        vis[v] = true;
        if (match[v] == 0 || dfs(match[v])) {
            match[v] = u;
            return true;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> m >> k)) return 0;

    adj.resize(n + 1);
    match.assign(m + 1, 0);

    for (int i = 0; i < k; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    int matches = 0;
    for (int i = 1; i <= n; ++i) {
        vis.assign(m + 1, false);
        if (dfs(i)) {
            matches++;
        }
    }

    cout << matches << "\n";
    for (int i = 1; i <= m; ++i) {
        if (match[i] != 0) {
            cout << match[i] << " " << i << "\n";
        }
    }

    return 0;
}