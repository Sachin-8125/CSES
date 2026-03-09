#include<bits/stdc++.h>
using namespace std;

int n, m;
vector<int> adj[100005];
int color[100005];   // 0=unvisited, 1=in stack, 2=done
int parent[100005];
int cycle_start, cycle_end;

bool dfs(int u) {
    color[u] = 1;  // mark in stack

    for (int v : adj[u]) {
        if (v == parent[u]) continue;  // skip the edge we came from

        if (color[v] == 1) {
            // Back edge found → cycle detected
            cycle_start = v;
            cycle_end = u;
            return true;
        }

        if (color[v] == 0) {
            parent[v] = u;
            if (dfs(v)) return true;
        }
    }

    color[u] = 2;  // done
    return false;
}

int main() {
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    memset(color, 0, sizeof(color));
    memset(parent, -1, sizeof(parent));
    cycle_start = -1;

    // Try each component
    for (int i = 1; i <= n; i++) {
        if (color[i] == 0) {
            if (dfs(i)) break;
        }
    }

    if (cycle_start == -1) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    // Reconstruct cycle from cycle_end back to cycle_start
    vector<int> cycle;
    for (int cur = cycle_end; cur != cycle_start; cur = parent[cur])
        cycle.push_back(cur);
    cycle.push_back(cycle_start);
    reverse(cycle.begin(), cycle.end());

    // Print: cycle_start appears at beginning AND end (round trip)
    cout << cycle.size() + 1 << "\n";
    for (int node : cycle)
        cout << node << " ";
    cout << cycle_start << "\n";  // return to start

    return 0;
}