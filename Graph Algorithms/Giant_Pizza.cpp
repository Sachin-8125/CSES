#include <iostream>
#include <vector>

using namespace std;

const int MAX = 200005;
vector<int> adj[MAX];
vector<int> rev_adj[MAX];
bool vis[MAX];
int scc[MAX];
vector<int> order;

void dfs1(int u) {
    vis[u] = true;
    for (int v : adj[u]) {
        if (!vis[v]) dfs1(v);
    }
    order.push_back(u);
}

void dfs2(int u, int k) {
    scc[u] = k;
    for (int v : rev_adj[u]) {
        if (!scc[v]) dfs2(v, k);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    for (int i = 0; i < n; ++i) {
        char c1, c2;
        int x1, x2;
        cin >> c1 >> x1 >> c2 >> x2;

        int u = (c1 == '+') ? x1 : x1 + m;
        int not_u = (c1 == '+') ? x1 + m : x1;
        
        int v = (c2 == '+') ? x2 : x2 + m;
        int not_v = (c2 == '+') ? x2 + m : x2;

        adj[not_u].push_back(v);
        adj[not_v].push_back(u);
        rev_adj[v].push_back(not_u);
        rev_adj[u].push_back(not_v);
    }

    for (int i = 1; i <= 2 * m; ++i) {
        if (!vis[i]) {
            dfs1(i);
        }
    }

    int k = 0;
    for (int i = 2 * m - 1; i >= 0; --i) {
        int u = order[i];
        if (!scc[u]) {
            k++;
            dfs2(u, k);
        }
    }

    for (int i = 1; i <= m; ++i) {
        if (scc[i] == scc[i + m]) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    for (int i = 1; i <= m; ++i) {
        if (scc[i] > scc[i + m]) {
            cout << "+ ";
        } else {
            cout << "- ";
        }
    }
    cout << "\n";

    return 0;
}