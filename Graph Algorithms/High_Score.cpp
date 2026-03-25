#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v;
    long long weight;
};

const long long INF = 1e18; 

int main() {
    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<Edge> edges(m);
    vector<vector<int>> adj(n + 1);
    vector<vector<int>> rev_adj(n + 1);

    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
        edges[i].weight = -edges[i].weight;
        adj[edges[i].u].push_back(edges[i].v);
        rev_adj[edges[i].v].push_back(edges[i].u);
    }

    // Reachability checks: Only paths from 1 to N matter
    vector<bool> reachable_from_1(n + 1, false);
    vector<bool> can_reach_n(n + 1, false);

    auto dfs = [&](auto self, int u, vector<bool>& vis, const vector<vector<int>>& graph) -> void {
        vis[u] = true;
        for (int v : graph[u]) {
            if (!vis[v]) self(self, v, vis, graph);
        }
    };

    dfs(dfs, 1, reachable_from_1, adj);
    dfs(dfs, n, can_reach_n, rev_adj);

    // Bellman-Ford Algorithm
    vector<long long> dist(n + 1, INF);
    dist[1] = 0;

    for (int i = 1; i <= n; ++i) {
        for (const auto& edge : edges) {
            if (dist[edge.u] != INF && dist[edge.v] > dist[edge.u] + edge.weight) {
                dist[edge.v] = dist[edge.u] + edge.weight;
                if (i == n) {
                    if (reachable_from_1[edge.v] && can_reach_n[edge.v]) {
                        cout << -1 << endl;
                        return 0;
                    }
                }
            }
        }
    }

    cout << -dist[n] << endl;
    return 0;
}
