#include <iostream>
#include <vector>

using namespace std;

void dfs1(int u, const vector<vector<int>>& adj, vector<bool>& vis, vector<int>& order) {
    vis[u] = true;
    for (int v : adj[u]) {
        if (!vis[v]) {
            dfs1(v, adj, vis, order);
        }
    }
    order.push_back(u);
}

void dfs2(int u, const vector<vector<int>>& rev_adj, vector<int>& kingdom, int k) {
    kingdom[u] = k;
    for (int v : rev_adj[u]) {
        if (!kingdom[v]) {
            dfs2(v, rev_adj, kingdom, k);
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

    vector<bool> vis(n + 1, false);
    vector<int> order;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            dfs1(i, adj, vis, order);
        }
    }

    vector<int> kingdom(n + 1, 0);
    int k = 0;
    for (int i = n - 1; i >= 0; i--) {
        int u = order[i];
        if (!kingdom[u]) {
            k++;
            dfs2(u, rev_adj, kingdom, k);
        }
    }

    cout << k << "\n";
    for (int i = 1; i <= n; i++) {
        cout << kingdom[i] << (i == n ? "" : " ");
    }
    cout << "\n";

    return 0;
}