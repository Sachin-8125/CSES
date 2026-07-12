#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> adj;
vector<int> state;
vector<int> parent_node;
int cycle_start = -1, cycle_end = -1;

bool dfs(int u) {
    state[u] = 1;
    for (int v : adj[u]) {
        if (state[v] == 0) {
            parent_node[v] = u;
            if (dfs(v)) return true;
        } else if (state[v] == 1) {
            cycle_end = u;
            cycle_start = v;
            return true;
        }
    }
    state[u] = 2;
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    adj.resize(n + 1);
    state.assign(n + 1, 0);
    parent_node.assign(n + 1, -1);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    for (int i = 1; i <= n; ++i) {
        if (state[i] == 0 && dfs(i)) {
            break;
        }
    }

    if (cycle_start == -1) {
        cout << "IMPOSSIBLE\n";
    } else {
        vector<int> cycle;
        cycle.push_back(cycle_start);
        for (int v = cycle_end; v != cycle_start; v = parent_node[v]) {
            cycle.push_back(v);
        }
        cycle.push_back(cycle_start);
        reverse(cycle.begin(), cycle.end());

        cout << cycle.size() << "\n";
        for (int node : cycle) {
            cout << node << " ";
        }
        cout << "\n";
    }

    return 0;
}