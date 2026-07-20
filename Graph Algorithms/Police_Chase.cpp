#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Edge {
    int to;
    long long cap, flow;
    int rev;
};

const long long INF = 1e18;
vector<vector<Edge>> adj;
vector<int> level;
vector<int> ptr;

void add_edge(int from, int to, long long cap) {
    adj[from].push_back({to, cap, 0, (int)adj[to].size()});
    adj[to].push_back({from, cap, 0, (int)adj[from].size() - 1});
}

bool bfs(int s, int t) {
    fill(level.begin(), level.end(), -1);
    level[s] = 0;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto& edge : adj[v]) {
            if (edge.cap - edge.flow > 0 && level[edge.to] == -1) {
                level[edge.to] = level[v] + 1;
                q.push(edge.to);
            }
        }
    }
    return level[t] != -1;
}

long long dfs(int v, int t, long long pushed) {
    if (pushed == 0) return 0;
    if (v == t) return pushed;
    for (int& cid = ptr[v]; cid < adj[v].size(); ++cid) {
        auto& edge = adj[v][cid];
        int tr = edge.to;
        if (level[v] + 1 != level[tr] || edge.cap - edge.flow == 0) continue;
        long long push = dfs(tr, t, min(pushed, edge.cap - edge.flow));
        if (push == 0) continue;
        edge.flow += push;
        adj[tr][edge.rev].flow -= push;
        return push;
    }
    return 0;
}

long long dinic(int s, int t) {
    long long flow = 0;
    while (bfs(s, t)) {
        fill(ptr.begin(), ptr.end(), 0);
        while (long long pushed = dfs(s, t, INF)) {
            flow += pushed;
        }
    }
    return flow;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    adj.resize(n + 1);
    level.resize(n + 1);
    ptr.resize(n + 1);

    vector<pair<int, int>> edges;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        edges.push_back({a, b});
        add_edge(a, b, 1);
    }

    long long max_flow = dinic(1, n);

    vector<bool> visited(n + 1, false);
    queue<int> q;
    q.push(1);
    visited[1] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto& edge : adj[u]) {
            if (edge.cap - edge.flow > 0 && !visited[edge.to]) {
                visited[edge.to] = true;
                q.push(edge.to);
            }
        }
    }

    cout << max_flow << "\n";
    for (auto& edge : edges) {
        if (visited[edge.first] != visited[edge.second]) {
            cout << edge.first << " " << edge.second << "\n";
        }
    }

    return 0;
}