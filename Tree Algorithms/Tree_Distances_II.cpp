#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

const int MAXN = 200005;
vector<int> adj[MAXN];
ll subtree_size[MAXN];
ll dist_sum[MAXN];
ll ans[MAXN];
int n;

void dfs1(int u, int p, int depth) {
    subtree_size[u] = 1;
    dist_sum[1] += depth;
    for (int v : adj[u]) {
        if (v != p) {
            dfs1(v, u, depth + 1);
            subtree_size[u] += subtree_size[v];
        }
    }
}

void dfs2(int u, int p) {
    for (int v : adj[u]) {
        if (v != p) {
            ans[v] = ans[u] + n - 2 * subtree_size[v];
            dfs2(v, u);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n)) return 0;
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs1(1, 0, 0);
    ans[1] = dist_sum[1];
    dfs2(1, 0);

    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << (i == n ? "" : " ");
    }
    cout << endl;

    return 0;
}
