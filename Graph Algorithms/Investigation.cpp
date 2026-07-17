#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const long long INF = 1e18;
const int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<pair<int, long long>>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        long long c;
        cin >> u >> v >> c;
        adj[u].push_back({v, c});
    }

    vector<long long> dist(n + 1, INF);
    vector<long long> ways(n + 1, 0);
    vector<int> min_e(n + 1, 0);
    vector<int> max_e(n + 1, 0);

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;

    dist[1] = 0;
    ways[1] = 1;
    pq.push({0, 1});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;

        for (auto& edge : adj[u]) {
            int v = edge.first;
            long long w = edge.second;

            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                ways[v] = ways[u];
                min_e[v] = min_e[u] + 1;
                max_e[v] = max_e[u] + 1;
                pq.push({dist[v], v});
            } else if (dist[u] + w == dist[v]) {
                ways[v] = (ways[v] + ways[u]) % MOD;
                if (min_e[u] + 1 < min_e[v]) min_e[v] = min_e[u] + 1;
                if (max_e[u] + 1 > max_e[v]) max_e[v] = max_e[u] + 1;
            }
        }
    }

    cout << dist[n] << " " << ways[n] << " " << min_e[n] << " " << max_e[n] << "\n";

    return 0;
}