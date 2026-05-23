#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5, L = 18;
vector<int> adj[N];
int up[N][L], depth[N];

void dfs(int u, int p) {
    up[u][0] = p;
    for (int i = 1; i < L; ++i) 
        up[u][i] = up[up[u][i - 1]][i - 1];
    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
        }
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    for (int i = L - 1; i >= 0; --i)
        if ((depth[u] - depth[v]) >> i & 1) u = up[u][i];
    if (u == v) return u;
    for (int i = L - 1; i >= 0; --i)
        if (up[u][i] != up[v][i]) u = up[u][i], v = up[v][i];
    return up[u][0];
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, q; 
    cin >> n >> q;
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, 1);
    while (q--) {
        int u, v; 
        cin >> u >> v;
        cout << depth[u] + depth[v] - 2 * depth[lca(u, v)] << "\n";
    }
}