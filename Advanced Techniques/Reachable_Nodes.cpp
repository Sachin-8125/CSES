#include <iostream>
#include <vector>
#include <bitset>
#include <queue>

using namespace std;

const int MAXN = 50000;

vector<int> adj[MAXN + 1];
bitset<MAXN> reach[MAXN + 1];
int indeg[MAXN + 1];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<int> outdeg(n + 1, 0);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        indeg[b]++;
    }

    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (indeg[i] == 0) q.push(i);
    }

    vector<int> topo;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topo.push_back(u);
        for (int v : adj[u]) {
            if (--indeg[v] == 0) q.push(v);
        }
    }

    for (int i = (int)topo.size() - 1; i >= 0; --i) {
        int u = topo[i];
        reach[u].set(u - 1);
        for (int v : adj[u]) {
            reach[u] |= reach[v];
        }
    }

    for (int i = 1; i <= n; ++i) {
        cout << reach[i].count() << (i == n ? "" : " ");
    }
    cout << "\n";

    return 0;
}