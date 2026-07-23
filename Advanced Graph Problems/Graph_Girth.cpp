#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int girth = INT_MAX;

    for (int s = 1; s <= n; s++) {
        vector<int> dist(n + 1, -1);
        vector<int> parent(n + 1, -1);
        queue<int> q;
        q.push(s);
        dist[s] = 0;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : adj[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    parent[v] = u;
                    q.push(v);
                } else if (v != parent[u]) {
                    int cycleLen = dist[u] + dist[v] + 1;
                    girth = min(girth, cycleLen);
                }
            }
        }
    }

    if (girth == INT_MAX) {
        cout << -1 << "\n";
    } else {
        cout << girth << "\n";
    }

    return 0;
}