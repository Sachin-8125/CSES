#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<int>> adj(n + 1);
    vector<int> indeg(n + 1, 0), outdeg(n + 1, 0);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        outdeg[a]++;
        indeg[b]++;
    }

    if (outdeg[1] != indeg[1] + 1 || indeg[n] != outdeg[n] + 1) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    for (int i = 2; i < n; i++) {
        if (indeg[i] != outdeg[i]) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    vector<int> idx(n + 1, 0);
    vector<int> st;
    vector<int> path;
    st.push_back(1);

    while (!st.empty()) {
        int u = st.back();
        if (idx[u] < (int)adj[u].size()) {
            st.push_back(adj[u][idx[u]++]);
        } else {
            path.push_back(u);
            st.pop_back();
        }
    }

    if ((int)path.size() != m + 1) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    for (int i = m; i >= 0; i--) {
        cout << path[i] << (i == 0 ? "\n" : " ");
    }

    return 0;
}
