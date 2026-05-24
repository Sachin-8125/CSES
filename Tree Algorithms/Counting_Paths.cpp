#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 200005;
const int LOG = 20;

vector<int> adj[MAXN];
int up[MAXN][LOG];
int depth[MAXN];
int val[MAXN];
int ans[MAXN];

void dfs_lca(int u, int p, int d) {
    depth[u] = d;
    up[u][0] = p;
    for (int i = 1; i < LOG; i++) {
        up[u][i] = up[up[u][i - 1]][i - 1];
    }
    for (int v : adj[u]) {
        if (v != p) {
            dfs_lca(v, u, d + 1);
        }
    }
}

int get_lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    for (int i = LOG - 1; i >= 0; i--) {
        if (depth[u] - (1 << i) >= depth[v]) {
            u = up[u][i];
        }
    }
    if (u == v) return u;
    for (int i = LOG - 1; i >= 0; i--) {
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }
    return up[u][0];
}

void dfs_ans(int u, int p) {
    ans[u] = val[u];
    for (int v : adj[u]) {
        if (v != p) {
            dfs_ans(v, u);
            ans[u] += ans[v];
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs_lca(1, 0, 0);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        int lca = get_lca(u, v);
        val[u]++;
        val[v]++;
        val[lca]--;
        if (up[lca][0] != 0) {
            val[up[lca][0]]--;
        }
    }

    dfs_ans(1, 0);

    for (int i = 1; i <= n; i++) {
        cout << ans[i] << (i == n ? "" : " ");
    }
    cout << endl;

    return 0;
}
