#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k;
    if (!(cin >> n >> m >> k)) return 0;

    vector<vector<pair<int, long long>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    vector<priority_queue<long long>> dist(n + 1);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;

    dist[1].push(0);
    pq.push({0, 1});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (dist[u].size() == k && d > dist[u].top()) {
            continue;
        }

        for (auto& edge : adj[u]) {
            int v = edge.first;
            long long w = edge.second;
            long long new_dist = d + w;

            if (dist[v].size() < k) {
                dist[v].push(new_dist);
                pq.push({new_dist, v});
            } else if (new_dist < dist[v].top()) {
                dist[v].pop();
                dist[v].push(new_dist);
                pq.push({new_dist, v});
            }
        }
    }

    vector<long long> ans;
    while (!dist[n].empty()) {
        ans.push_back(dist[n].top());
        dist[n].pop();
    }

    for (int i = k - 1; i >= 0; i--) {
        cout << ans[i] << (i == 0 ? "" : " ");
    }
    cout << "\n";

    return 0;
}