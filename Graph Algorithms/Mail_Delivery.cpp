#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <stack>

using namespace std;



const int MAXN = 100005;
vector<pair<int, int>> adj[MAXN];
bool used_edge[200005];
int degree[MAXN];
int head_ptr[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
        degree[u]++;
        degree[v]++;
    }

    for (int i = 1; i <= n; ++i) {
        if (degree[i] % 2 != 0) {
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }
    }

    vector<int> circuit;
    stack<int> st;
    st.push(1);

    while (!st.empty()) {
        int u = st.top();
        bool found_edge = false;

        while (head_ptr[u] < adj[u].size()) {
            pair<int, int> edge = adj[u][head_ptr[u]++];
            int v = edge.first;
            int id = edge.second;

            if (!used_edge[id]) {
                used_edge[id] = true;
                st.push(v);
                found_edge = true;
                break;
            }
        }

        if (!found_edge) {
            circuit.push_back(u);
            st.pop();
        }
    }

    if (circuit.size() != m + 1) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        for (int i = 0; i < circuit.size(); ++i) {
            cout << circuit[i] << (i == circuit.size() - 1 ? "" : " ");
        }
        cout << endl;
    }

    return 0;
}