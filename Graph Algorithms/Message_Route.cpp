#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // BFS from node 1
    vector<int> dist(n + 1, -1);
    vector<int> parent(n + 1, -1);  // to reconstruct path
    queue<int> q;

    dist[1] = 0;
    q.push(1);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                parent[v] = u;        // track where we came from
                q.push(v);
            }
        }
    }

    // Check if node n is reachable
    if (dist[n] == -1) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    // Reconstruct path from n back to 1
    vector<int> path;
    for (int cur = n; cur != -1; cur = parent[cur])
        path.push_back(cur);

    reverse(path.begin(), path.end());

    cout << path.size() << "\n";
    for (int node : path)
        cout << node << " ";
    cout << "\n";

    return 0;
}