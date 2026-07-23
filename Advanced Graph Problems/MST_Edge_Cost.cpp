#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v;
    long long w;
    int id;
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

struct DSU {
    vector<int> parent, sz;
    DSU(int n) {
        parent.resize(n + 1);
        sz.resize(n + 1, 1);
        for (int i = 1; i <= n; ++i) {
            parent[i] = i;
        }
    }
    int find(int i) {
        if (i == parent[i]) return i;
        return parent[i] = find(parent[i]);
    }
    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i == root_j) return false;
        if (sz[root_i] < sz[root_j]) swap(root_i, root_j);
        parent[root_j] = root_i;
        sz[root_i] += sz[root_j];
        return true;
    }
};

const int MAXN = 100005;
const int LOG = 20;

vector<pair<int, long long>> adj[MAXN];
int up[MAXN][LOG];
long long mx_wt[MAXN][LOG];
int depth[MAXN];

void dfs(int u, int p, int d, long long w) {
    depth[u] = d;
    up[u][0] = p;
    mx_wt[u][0] = w;
    
    for (int i = 1; i < LOG; ++i) {
        up[u][i] = up[up[u][i - 1]][i - 1];
        mx_wt[u][i] = max(mx_wt[u][i - 1], mx_wt[up[u][i - 1]][i - 1]);
    }
    
    for (const auto& edge : adj[u]) {
        int v = edge.first;
        if (v != p) {
            dfs(v, u, d + 1, edge.second);
        }
    }
}

long long query_max(int u, int v) {
    long long res = 0;
    if (depth[u] < depth[v]) swap(u, v);
    
    int diff = depth[u] - depth[v];
    for (int i = 0; i < LOG; ++i) {
        if ((diff >> i) & 1) {
            res = max(res, mx_wt[u][i]);
            u = up[u][i];
        }
    }
    
    if (u == v) return res;
    
    for (int i = LOG - 1; i >= 0; --i) {
        if (up[u][i] != up[v][i]) {
            res = max(res, mx_wt[u][i]);
            res = max(res, mx_wt[v][i]);
            u = up[u][i];
            v = up[v][i];
        }
    }
    
    res = max({res, mx_wt[u][0], mx_wt[v][0]});
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<Edge> edges(m);
    vector<Edge> sorted_edges(m);
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        edges[i].id = i;
        sorted_edges[i] = edges[i];
    }

    sort(sorted_edges.begin(), sorted_edges.end());

    DSU dsu(n);
    long long mst_weight = 0;
    vector<bool> in_mst(m, false);

    for (const auto& edge : sorted_edges) {
        if (dsu.unite(edge.u, edge.v)) {
            mst_weight += edge.w;
            in_mst[edge.id] = true;
            adj[edge.u].push_back({edge.v, edge.w});
            adj[edge.v].push_back({edge.u, edge.w});
        }
    }

    dfs(1, 1, 0, 0);

    for (int i = 0; i < m; ++i) {
        if (in_mst[i]) {
            cout << mst_weight << "\n";
        } else {
            long long max_cycle_edge = query_max(edges[i].u, edges[i].v);
            cout << mst_weight + edges[i].w - max_cycle_edge << "\n";
        }
    }

    return 0;
}