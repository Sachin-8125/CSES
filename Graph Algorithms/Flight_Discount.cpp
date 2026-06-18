#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 1e15;

struct Edge {
    int to;
    ll cost;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m; cin >> n >> m;
    vector<vector<Edge>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int a,b; ll c; cin >> a >> b >> c;
        adj[a].push_back({b, c});
    }

    vector<vector<ll>> dist(n + 1, vector<ll>(2, INF));
    dist[1][0] = 0;

    using T = tuple<ll,int,int>;
    priority_queue<T, vector<T>, greater<T>> pq;
    pq.emplace(0, 1, 0);

    while (!pq.empty()) {
        auto [cur_cost, u, used] = pq.top(); pq.pop();
        if (cur_cost > dist[u][used]) continue;

        for (auto &e : adj[u]) {
            int v = e.to;
            ll c = e.cost;

            if (dist[v][used] > cur_cost + c) {
                dist[v][used] = cur_cost + c;
                pq.emplace(dist[v][used], v, used);
            }

            if (used == 0) {
                ll discounted = cur_cost + (c / 2);
                if (dist[v][1] > discounted) {
                    dist[v][1] = discounted;
                    pq.emplace(dist[v][1], v, 1);
                }
            }
        }
    }

    cout << min(dist[n][0], dist[n][1]) << "\n";

    return 0;
}