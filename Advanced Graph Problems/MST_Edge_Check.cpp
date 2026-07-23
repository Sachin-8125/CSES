#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v, w, id;
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

struct DSU {
    vector<int> parent;
    
    DSU(int n) {
        parent.resize(n + 1);
        for (int i = 1; i <= n; ++i) {
            parent[i] = i;
        }
    }

    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }

    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        edges[i].id = i;
    }

    sort(edges.begin(), edges.end());

    DSU dsu(n);
    vector<bool> ans(m, false);

    for (int i = 0; i < m; ) {
        int j = i;
        while (j < m && edges[j].w == edges[i].w) {
            j++;
        }

        for (int k = i; k < j; ++k) {
            if (dsu.find(edges[k].u) != dsu.find(edges[k].v)) {
                ans[edges[k].id] = true;
            }
        }

        for (int k = i; k < j; ++k) {
            dsu.unite(edges[k].u, edges[k].v);
        }

        i = j;
    }

    for (int i = 0; i < m; ++i) {
        if (ans[i]) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}