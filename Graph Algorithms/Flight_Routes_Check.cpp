#include <iostream>
#include <vector>

using namespace std;

void dfs(int u, const vector<vector<int>>& adj, vector<bool>& vis) {
    vis[u] = true;
    for (int v : adj[u]) {
        if (!vis[v]) {
            dfs(v, adj, vis);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<int>> adj(n + 1);
    vector<vector<int>> rev_adj(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        rev_adj[v].push_back(u);
    }

    vector<bool> vis1(n + 1, false);
    dfs(1, adj, vis1);

    for (int i = 1; i <= n; i++) {
        if (!vis1[i]) {
            cout << "NO\n";
            cout << 1 << " " << i << "\n";
            return 0;
        }
    }

    vector<bool> vis2(n + 1, false);
    dfs(1, rev_adj, vis2);

    for (int i = 1; i <= n; i++) {
        if (!vis2[i]) {
            cout << "NO\n";
            cout << i << " " << 1 << "\n";
            return 0;
        }
    }

    cout << "YES\n";

    return 0;
}