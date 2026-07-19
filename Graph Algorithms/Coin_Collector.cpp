#include <iostream>
#include <vector>

using namespace std;

const int MAX = 100005;
long long k[MAX];
vector<int> adj[MAX];
vector<int> rev_adj[MAX];
bool vis[MAX];
int scc[MAX];
long long scc_weight[MAX];
vector<int> order;

void dfs1(int u) {
    vis[u] = true;
    for (int v : adj[u]) {
        if (!vis[v]) dfs1(v);
    }
    order.push_back(u);
}

void dfs2(int u, int c) {
    scc[u] = c;
    scc_weight[c] += k[u];
    for (int v : rev_adj[u]) {
        if (!scc[v]) dfs2(v, c);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    for (int i = 1; i <= n; i++) {
        cin >> k[i];
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        rev_adj[v].push_back(u);
    }

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) dfs1(i);
    }

    int num_scc = 0;
    for (int i = n - 1; i >= 0; i--) {
        int u = order[i];
        if (!scc[u]) {
            num_scc++;
            dfs2(u, num_scc);
        }
    }

    vector<vector<int>> dag_adj(num_scc + 1);
    for (int u = 1; u <= n; u++) {
        for (int v : adj[u]) {
            if (scc[u] != scc[v]) {
                dag_adj[scc[u]].push_back(scc[v]);
            }
        }
    }

    vector<long long> dp(num_scc + 1, 0);
    long long ans = 0;
    for (int i = 1; i <= num_scc; i++) {
        dp[i] = max(dp[i], scc_weight[i]);
        for (int v : dag_adj[i]) {
            dp[v] = max(dp[v], dp[i] + scc_weight[v]);
        }
        ans = max(ans, dp[i]);
    }

    cout << ans << "\n";

    return 0;
}