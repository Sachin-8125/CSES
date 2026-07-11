#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int a, b;
    long long c;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].a >> edges[i].b >> edges[i].c;
    }

    vector<long long> dist(n + 1, 0);
    vector<int> par(n + 1, -1);

    int x = -1;
    for (int i = 0; i < n; i++) {
        x = -1;
        for (auto &e : edges) {
            if (dist[e.a] + e.c < dist[e.b]) {
                dist[e.b] = dist[e.a] + e.c;
                par[e.b] = e.a;
                x = e.b;
            }
        }
    }

    if (x == -1) {
        cout << "NO\n";
        return 0;
    }

    for (int i = 0; i < n; i++) x = par[x];

    vector<int> cycle;
    int v = x;
    do {
        cycle.push_back(v);
        v = par[v];
    } while (v != x);
    cycle.push_back(x);
    reverse(cycle.begin(), cycle.end());

    cout << "YES\n";
    for (int node : cycle) cout << node << ' ';
    cout << '\n';

    return 0;
}