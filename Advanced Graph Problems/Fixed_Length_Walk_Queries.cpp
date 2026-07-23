#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAXN = 2505;
int dist[MAXN][MAXN][2];
vector<int> adj[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, q;
    if (!(cin >> n >> m >> q)) return 0;

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            dist[i][j][0] = -1;
            dist[i][j][1] = -1;
        }
    }

    for (int i = 1; i <= n; ++i) {
        queue<pair<int, int>> qu;
        dist[i][i][0] = 0;
        qu.push({i, 0});

        while (!qu.empty()) {
            auto [u, p] = qu.front();
            qu.pop();

            int np = p ^ 1;
            for (int v : adj[u]) {
                if (dist[i][v][np] == -1) {
                    dist[i][v][np] = dist[i][u][p] + 1;
                    qu.push({v, np});
                }
            }
        }
    }

    for (int i = 0; i < q; ++i) {
        int a, b;
        int x;
        cin >> a >> b >> x;

        int p = x % 2;
        if (dist[a][b][p] != -1 && dist[a][b][p] <= x) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}