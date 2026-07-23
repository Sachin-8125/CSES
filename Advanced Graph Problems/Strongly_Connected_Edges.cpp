#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<int>> adj(n + 1);
    vector<pair<int, int>> edges(m);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        edges[i] = {u, v};
    }

    vector<int> tin(n + 1, -1), low(n + 1, -1), parent(n + 1, 0);
    int timer = 0;
    bool has_bridge = false;

    struct Frame {
        int u, p;
        int idx;
    };

    stack<Frame> st;
    st.push({1, 0, 0});
    tin[1] = low[1] = timer++;

    while (!st.empty()) {
        auto& f = st.top();
        int u = f.u;
        int p = f.p;

        if (f.idx < (int)adj[u].size()) {
            int v = adj[u][f.idx];
            f.idx++;
            if (v == p) continue;

            if (tin[v] != -1) {
                low[u] = min(low[u], tin[v]);
            } else {
                parent[v] = u;
                tin[v] = low[v] = timer++;
                st.push({v, u, 0});
            }
        } else {
            st.pop();
            if (!st.empty()) {
                auto& parent_frame = st.top();
                int pu = parent_frame.u;
                low[pu] = min(low[pu], low[u]);
                if (low[u] > tin[pu]) {
                    has_bridge = true;
                }
            }
        }
    }

    if (timer < n || has_bridge) {
        cout << "IMPOSSIBLE\n";
    } else {
        for (int i = 0; i < m; ++i) {
            int u = edges[i].first;
            int v = edges[i].second;
            if (parent[u] == v) {
                cout << v << " " << u << "\n";
            } else if (parent[v] == u) {
                cout << u << " " << v << "\n";
            } else {
                if (tin[u] > tin[v]) {
                    cout << u << " " << v << "\n";
                } else {
                    cout << v << " " << u << "\n";
                }
            }
        }
    }

    return 0;
}