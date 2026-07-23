#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> U(m), V(m);
    vector<vector<int>> adj(n + 1);
    vector<char> rhs(n + 1, 0);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        U[i] = a;
        V[i] = b;
        adj[a].push_back(i);
        adj[b].push_back(i);
        rhs[b] ^= 1;
    }

    vector<int> parent(n + 1, -1), parentEdge(n + 1, -1);
    vector<char> vis(n + 1, 0);

    vector<int> order;
    order.reserve(n);
    vector<int> roots;
    roots.reserve(n);

    for (int s = 1; s <= n; s++) {
        if (vis[s]) continue;
        vis[s] = 1;
        parent[s] = -1;
        parentEdge[s] = -1;
        roots.push_back(s);
        order.push_back(s);

        deque<int> dq;
        dq.push_back(s);
        while (!dq.empty()) {
            int x = dq.front();
            dq.pop_front();
            for (int eid : adj[x]) {
                int y = (U[eid] == x) ? V[eid] : U[eid];
                if (!vis[y]) {
                    vis[y] = 1;
                    parent[y] = x;
                    parentEdge[y] = eid;
                    dq.push_back(y);
                    order.push_back(y);
                }
            }
        }
    }

    vector<char> x(m, 0);
    vector<char> degParity(n + 1, 0);

    for (int i = (int)order.size() - 1; i >= 0; i--) {
        int v = order[i];
        if (parent[v] == -1) continue;
        int pe = parentEdge[v];
        char xv = rhs[v] ^ degParity[v];
        x[pe] = xv;
        degParity[parent[v]] ^= xv;
    }

    for (int r : roots) {
        if (degParity[r] != rhs[r]) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    for (int i = 0; i < m; i++) {
        if (x[i]) cout << U[i] << " " << V[i] << "\n";
        else cout << V[i] << " " << U[i] << "\n";
    }
    return 0;
}