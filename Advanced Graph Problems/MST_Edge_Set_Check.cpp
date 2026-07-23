#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v, w, id;
};

struct QueryEdge {
    int w, q_id, u, v;
    bool operator<(const QueryEdge& other) const {
        if (w != other.w) return w < other.w;
        return q_id < other.q_id;
    }
};

struct RollbackDSU {
    vector<int> parent, sz;
    struct Change { int v, p_v, u, sz_u; };
    vector<Change> history;

    RollbackDSU(int n) {
        parent.resize(n + 1);
        sz.resize(n + 1, 1);
        for (int i = 1; i <= n; ++i) parent[i] = i;
    }

    int find(int i) {
        while (i != parent[i]) i = parent[i];
        return i;
    }

    bool unite(int i, int j) {
        int u = find(i);
        int v = find(j);
        if (u == v) return false;
        if (sz[u] < sz[v]) swap(u, v);
        history.push_back({v, parent[v], u, sz[u]});
        parent[v] = u;
        sz[u] += sz[v];
        return true;
    }

    void rollback(size_t state) {
        while (history.size() > state) {
            Change c = history.back();
            history.pop_back();
            parent[c.v] = c.p_v;
            sz[c.u] = c.sz_u;
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, q;
    if (!(cin >> n >> m >> q)) return 0;

    vector<Edge> edges(m + 1);
    vector<Edge> sorted_edges;
    sorted_edges.reserve(m);
    for (int i = 1; i <= m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        edges[i].id = i;
        sorted_edges.push_back(edges[i]);
    }

    sort(sorted_edges.begin(), sorted_edges.end(), [](const Edge& a, const Edge& b) {
        return a.w < b.w;
    });

    vector<QueryEdge> q_edges;
    for (int i = 0; i < q; ++i) {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j) {
            int idx;
            cin >> idx;
            q_edges.push_back({edges[idx].w, i, edges[idx].u, edges[idx].v});
        }
    }

    sort(q_edges.begin(), q_edges.end());

    vector<bool> ans(q, true);
    RollbackDSU dsu(n);

    int i = 0;
    int j = 0;
    int num_q_edges = q_edges.size();
    int num_edges = sorted_edges.size();

    while (j < num_q_edges) {
        int w = q_edges[j].w;

        while (i < num_edges && sorted_edges[i].w < w) {
            dsu.unite(sorted_edges[i].u, sorted_edges[i].v);
            i++;
        }
        
        dsu.history.clear(); 

        int k = j;
        while (k < num_q_edges && q_edges[k].w == w) {
            int q_id = q_edges[k].q_id;
            int end_k = k;
            while (end_k < num_q_edges && q_edges[end_k].w == w && q_edges[end_k].q_id == q_id) {
                end_k++;
            }

            if (ans[q_id]) {
                size_t state = dsu.history.size();
                for (int x = k; x < end_k; ++x) {
                    if (!dsu.unite(q_edges[x].u, q_edges[x].v)) {
                        ans[q_id] = false;
                        break;
                    }
                }
                dsu.rollback(state);
            }
            
            k = end_k;
        }
        j = k;
    }

    for (int idx = 0; idx < q; ++idx) {
        if (ans[idx]) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}