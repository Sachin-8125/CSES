#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<pair<int, long long>>> adj(n + 1);

    for (int i = 0; i < m; ++i) {
        int l, r;
        long long s;
        cin >> l >> r >> s;
        adj[l - 1].push_back({r, s});
        adj[r].push_back({l - 1, -s});
    }

    vector<long long> P(n + 1, 0);
    vector<bool> visited(n + 1, false);

    for (int i = 0; i <= n; ++i) {
        if (!visited[i]) {
            visited[i] = true;
            P[i] = 0;
            queue<int> Q;
            Q.push(i);

            while (!Q.empty()) {
                int u = Q.front();
                Q.pop();

                for (auto& edge : adj[u]) {
                    int v = edge.first;
                    long long w = edge.second;

                    if (!visited[v]) {
                        visited[v] = true;
                        P[v] = P[u] + w;
                        Q.push(v);
                    } else {
                        if (P[v] != P[u] + w) {
                            cout << "NO\n";
                            return 0;
                        }
                    }
                }
            }
        }
    }

    cout << "YES\n";
    for (int i = 1; i <= n; ++i) {
        cout << P[i] - P[i - 1] << (i == n ? "" : " ");
    }
    cout << "\n";

    return 0;
}