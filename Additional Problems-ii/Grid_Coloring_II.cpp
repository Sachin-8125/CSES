#include <iostream>
#include <vector>
#include <string>

using namespace std;

int n, m;
vector<vector<int>> adj, rev_adj;
vector<bool> vis;
vector<int> order, comp;

void dfs1(int u) {
    vis[u] = true;
    for (int v : adj[u]) {
        if (!vis[v]) dfs1(v);
    }
    order.push_back(u);
}

void dfs2(int u, int id) {
    comp[u] = id;
    for (int v : rev_adj[u]) {
        if (comp[v] == -1) dfs2(v, id);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> m)) return 0;

    vector<string> grid(n);
    for (int i = 0; i < n; i++) cin >> grid[i];

    int total_vars = n * m;
    int total_nodes = 2 * total_vars;
    adj.resize(total_nodes);
    rev_adj.resize(total_nodes);

    vector<vector<char>> op(total_vars, vector<char>(2));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int u = i * m + j;
            int idx = 0;
            for (char c : {'A', 'B', 'C'}) {
                if (c != grid[i][j]) {
                    op[u][idx++] = c;
                }
            }
        }
    }

    auto add_edge = [&](int u, int v) {
        adj[u].push_back(v);
        rev_adj[v].push_back(u);
    };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int u = i * m + j;
            
            if (j + 1 < m) {
                int v = i * m + (j + 1);
                for (int x = 0; x < 2; x++) {
                    for (int y = 0; y < 2; y++) {
                        if (op[u][x] == op[v][y]) {
                            add_edge(2 * u + x, 2 * v + (1 - y));
                            add_edge(2 * v + y, 2 * u + (1 - x));
                        }
                    }
                }
            }
            
            if (i + 1 < n) {
                int v = (i + 1) * m + j;
                for (int x = 0; x < 2; x++) {
                    for (int y = 0; y < 2; y++) {
                        if (op[u][x] == op[v][y]) {
                            add_edge(2 * u + x, 2 * v + (1 - y));
                            add_edge(2 * v + y, 2 * u + (1 - x));
                        }
                    }
                }
            }
        }
    }

    vis.assign(total_nodes, false);
    order.reserve(total_nodes);
    for (int i = 0; i < total_nodes; i++) {
        if (!vis[i]) dfs1(i);
    }

    comp.assign(total_nodes, -1);
    int scc_id = 0;
    for (int i = total_nodes - 1; i >= 0; i--) {
        int u = order[i];
        if (comp[u] == -1) {
            dfs2(u, scc_id++);
        }
    }

    vector<int> ans(total_vars);
    for (int i = 0; i < total_vars; i++) {
        if (comp[2 * i] == comp[2 * i + 1]) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
        ans[i] = comp[2 * i] > comp[2 * i + 1] ? 0 : 1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int u = i * m + j;
            cout << op[u][ans[u]];
        }
        cout << "\n";
    }

    return 0;
}