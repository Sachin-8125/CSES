#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;
vector<vector<int>> adj;
vector<bool> visited;
vector<int> tin, low;
int timer;
vector<bool> is_cutpoint;

void dfs(int v, int p = -1) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    int children = 0;
    for (int to : adj[v]) {
        if (to == p) continue;
        if (visited[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] >= tin[v] && p != -1) {
                is_cutpoint[v] = true;
            }
            ++children;
        }
    }
    if (p == -1 && children > 1) {
        is_cutpoint[v] = true;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> m)) return 0;

    adj.resize(n + 1);
    visited.assign(n + 1, false);
    tin.assign(n + 1, -1);
    low.assign(n + 1, -1);
    is_cutpoint.assign(n + 1, false);
    timer = 0;

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(1);

    vector<int> ans;
    for (int i = 1; i <= n; ++i) {
        if (is_cutpoint[i]) {
            ans.push_back(i);
        }
    }

    cout << ans.size() << "\n";
    for (int i = 0; i < (int)ans.size(); ++i) {
        cout << ans[i] << (i == (int)ans.size() - 1 ? "" : " ");
    }
    cout << "\n";

    return 0;
}