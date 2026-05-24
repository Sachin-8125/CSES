#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 200005;
vector<int> adj[MAXN];
int parent[MAXN], depth[MAXN], heavy[MAXN], head[MAXN], pos[MAXN];
int sz[MAXN], val[MAXN];
int tree[2 * MAXN];
int n, q, cur_pos;

void dfs_sz(int u) {
    sz[u] = 1;
    heavy[u] = -1;
    for (int v : adj[u]) {
        if (v != parent[u]) {
            parent[v] = u;
            depth[v] = depth[u] + 1;
            dfs_sz(v);
            sz[u] += sz[v];
            if (heavy[u] == -1 || sz[v] > sz[heavy[u]]) {
                heavy[u] = v;
            }
        }
    }
}

void dfs_hld(int u, int h) {
    head[u] = h;
    pos[u] = cur_pos++;
    if (heavy[u] != -1) {
        dfs_hld(heavy[u], h);
    }
    for (int v : adj[u]) {
        if (v != parent[u] && v != heavy[u]) {
            dfs_hld(v, v);
        }
    }
}

void update(int p, int value) {
    for (tree[p += n] = value; p > 1; p >>= 1) {
        tree[p >> 1] = max(tree[p], tree[p ^ 1]);
    }
}

int query(int l, int r) {
    int res = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res = max(res, tree[l++]);
        if (r & 1) res = max(res, tree[--r]);
    }
    return res;
}

int path_query(int u, int v) {
    int res = 0;
    while (head[u] != head[v]) {
        if (depth[head[u]] > depth[head[v]]) swap(u, v);
        res = max(res, query(pos[head[v]], pos[v] + 1));
        v = parent[head[v]];
    }
    if (depth[u] > depth[v]) swap(u, v);
    res = max(res, query(pos[u], pos[v] + 1));
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> q)) return 0;

    for (int i = 1; i <= n; i++) cin >> val[i];

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs_sz(1);
    dfs_hld(1, 1);

    for (int i = 1; i <= n; i++) {
        tree[pos[i] + n] = val[i];
    }
    for (int i = n - 1; i > 0; --i) {
        tree[i] = max(tree[i << 1], tree[i << 1 | 1]);
    }

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int s, x;
            cin >> s >> x;
            update(pos[s], x);
        } else {
            int u, v;
            cin >> u >> v;
            cout << path_query(u, v) << " ";
        }
    }
    cout << "\n";

    return 0;
}
