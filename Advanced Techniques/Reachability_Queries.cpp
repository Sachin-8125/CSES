#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>

using namespace std;

const int MAXN = 50000;

vector<int> adj[MAXN + 1];
vector<int> radj[MAXN + 1];
bool vis[MAXN + 1];
int comp[MAXN + 1];
vector<int> order_list;

void dfs1(int u) {
    vis[u] = true;
    for (int v : adj[u]) if (!vis[v]) dfs1(v);
    order_list.push_back(u);
}

void dfs2(int u, int c) {
    comp[u] = c;
    for (int v : radj[u]) if (comp[v] == -1) dfs2(v, c);
}

bitset<MAXN> reach[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, q;
    if (!(cin >> n >> m >> q)) return 0;

    vector<int> ea(m), eb(m);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        ea[i] = a; eb[i] = b;
        adj[a].push_back(b);
        radj[b].push_back(a);
    }

    for (int i = 1; i <= n; ++i) if (!vis[i]) dfs1(i);

    fill(comp + 1, comp + n + 1, -1);
    int nc = 0;
    for (int i = (int)order_list.size() - 1; i >= 0; --i) {
        int u = order_list[i];
        if (comp[u] == -1) {
            dfs2(u, nc);
            nc++;
        }
    }

    vector<vector<int>> dag(nc);
    for (int i = 0; i < m; ++i) {
        int cu = comp[ea[i]], cv = comp[eb[i]];
        if (cu != cv) dag[cu].push_back(cv);
    }

    for (int c = nc - 1; c >= 0; --c) {
        reach[c].set(c);
        for (int nb : dag[c]) {
            reach[c] |= reach[nb];
        }
    }

    string out;
    while (q--) {
        int a, b;
        cin >> a >> b;
        if (reach[comp[a]].test(comp[b])) out += "YES\n";
        else out += "NO\n";
    }
    cout << out;

    return 0;
}