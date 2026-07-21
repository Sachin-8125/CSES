#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;
vector<vector<int>> adj;
vector<bool> visited;
vector<int> tin, low;
int timer;
vector<pair<int, int>> bridges;

void dfs(int v, int p = -1) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    for (int to : adj[v]) {
        if (to == p) continue;
        if (visited[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] > tin[v]) {
                bridges.push_back({v, to});
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> m)) return 0;

    adj.resize(n + 1);
    visited.assign(n + 1, false);
    tin.assign(n + 1, -1);
    low.assign(n + 1, -1);
    timer = 0;

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            dfs(i);
        }
    }

    cout << bridges.size() << "\n";
    for (auto& edge : bridges) {
        cout << edge.first << " " << edge.second << "\n";
    }

    return 0;
}