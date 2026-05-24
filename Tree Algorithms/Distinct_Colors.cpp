#include <iostream>
#include <vector>
#include <set>

using namespace std;

const int MAXN = 200005;
vector<int> adj[MAXN];
int color[MAXN];
int ans[MAXN];
set<int>* st[MAXN];

void dfs(int u, int p) {
    int max_sz = -1, heavy_child = -1;
    
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
            if ((int)st[v]->size() > max_sz) {
                max_sz = st[v]->size();
                heavy_child = v;
            }
        }
    }

    if (heavy_child == -1) {
        st[u] = new set<int>();
    } else {
        st[u] = st[heavy_child];
    }

    for (int v : adj[u]) {
        if (v != p && v != heavy_child) {
            for (int c : *st[v]) {
                st[u]->insert(c);
            }
        }
    }
    
    st[u]->insert(color[u]);
    ans[u] = st[u]->size();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    for (int i = 1; i <= n; i++) {
        cin >> color[i];
    }

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, 0);

    for (int i = 1; i <= n; i++) {
        cout << ans[i] << (i == n ? "" : " ");
    }
    cout << "\n";

    return 0;
}