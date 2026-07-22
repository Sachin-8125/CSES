#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1e9;

struct State {
    int u;
    int origin;
    int d;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k;
    if (!(cin >> n >> m >> k)) return 0;

    vector<int> shops(k);
    vector<bool> is_shop(n + 1, false);
    
    for (int i = 0; i < k; ++i) {
        cin >> shops[i];
        is_shop[shops[i]] = true;
    }

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<pair<int, int>> dist1(n + 1, {INF, -1});
    vector<pair<int, int>> dist2(n + 1, {INF, -1});
    
    queue<State> q;

    for (int x : shops) {
        dist1[x] = {0, x};
        q.push({x, x, 0});
    }

    while (!q.empty()) {
        auto [u, origin, d] = q.front();
        q.pop();

        if (d > dist2[u].first) continue;

        for (int v : adj[u]) {
            int nd = d + 1;
            
            if (nd < dist1[v].first) {
                if (dist1[v].second != origin) {
                    dist2[v] = dist1[v];
                }
                dist1[v] = {nd, origin};
                q.push({v, origin, nd});
            } 
            else if (nd < dist2[v].first && origin != dist1[v].second) {
                dist2[v] = {nd, origin};
                q.push({v, origin, nd});
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        int ans = -1;
        if (is_shop[i]) {
            if (dist2[i].first != INF) {
                ans = dist2[i].first;
            }
        } else {
            if (dist1[i].first != INF) {
                ans = dist1[i].first;
            }
        }
        cout << ans << (i == n ? "" : " ");
    }
    cout << "\n";

    return 0;
}