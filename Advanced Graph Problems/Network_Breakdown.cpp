#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

struct DSU {
    vector<int> parent;
    int components;

    DSU(int n) {
        parent.resize(n + 1);
        for (int i = 1; i <= n; ++i) {
            parent[i] = i;
        }
        components = n;
    }

    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }

    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
            components--;
            return true;
        }
        return false;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k;
    if (!(cin >> n >> m >> k)) return 0;

    set<pair<int, int>> edges;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        if (u > v) swap(u, v);
        edges.insert({u, v});
    }

    vector<pair<int, int>> breakdowns(k);
    for (int i = 0; i < k; ++i) {
        int u, v;
        cin >> u >> v;
        if (u > v) swap(u, v);
        breakdowns[i] = {u, v};
        edges.erase({u, v});
    }

    DSU dsu(n);

    for (const auto& edge : edges) {
        dsu.unite(edge.first, edge.second);
    }

    vector<int> ans(k);
    for (int i = k - 1; i >= 0; --i) {
        ans[i] = dsu.components;
        dsu.unite(breakdowns[i].first, breakdowns[i].second);
    }

    for (int i = 0; i < k; ++i) {
        cout << ans[i] << (i == k - 1 ? "" : " ");
    }
    cout << "\n";

    return 0;
}