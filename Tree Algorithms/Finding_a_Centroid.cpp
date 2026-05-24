#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 200005;
vector<int> adj[MAXN];
int sz[MAXN];
int n;

void dfs_sz(int u, int p) {
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v != p) {
            dfs_sz(v, u);
            sz[u] += sz[v];
        }
    }
}

int find_centroid(int u, int p) {
    for (int v : adj[u]) {
        if (v != p && sz[v] > n / 2) {
            return find_centroid(v, u);
        }
    }
    return u;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n)) return 0;

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs_sz(1, 0);
    cout << find_centroid(1, 0) << endl;

    return 0;
}