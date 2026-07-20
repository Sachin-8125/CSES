#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Edge {
    int to;
    int cap, flow;
    int rev;
};

const int INF = 1e9;
vector<vector<Edge>> adj;
vector<int> level;
vector<int> ptr;

void add_edge(int from, int to, int cap) {
    adj[from].push_back({to, cap, 0, (int)adj[to].size()});
    adj[to].push_back({from, 0, 0, (int)adj[from].size() - 1});
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

int dfs(int v, int t, int pushed) {
    if (pushed == 0) return 0;
    if (v == t) return pushed;
    for (int& cid = ptr[v]; cid < adj[v].size(); ++cid) {
        auto& edge = adj[v][cid];
        int tr = edge.to;
        if (level[v] + 1 != level[tr] || edge.cap - edge.flow == 0) continue;
        int push = dfs(tr, t, min(pushed, edge.cap - edge.flow));
        if (push == 0) continue;
        edge.flow += push;
        adj[tr][edge.rev].flow -= push;
        return push;
    }
    return 0;
}

int dinic(int s, int t) {
    int flow = 0;
    while (bfs(s, t)) {
        fill(ptr.begin(), ptr.end(), 0);
        while (int pushed = dfs(s, t, INF)) {
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

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        add_edge(a, b, 1);
    }

    int max_flow = dinic(1, n);

    cout << max_flow << "\n";

    for (int i = 0; i < max_flow; ++i) {
        vector<int> path;
        int curr = 1;
        path.push_back(1);
        while (curr != n) {
            for (auto& edge : adj[curr]) {
                if (edge.cap == 1 && edge.flow == 1) {
                    edge.flow = 0;
                    curr = edge.to;
                    path.push_back(curr);
                    break;
                }
            }
        }
        cout << path.size() << "\n";
        for (int j = 0; j < (int)path.size(); ++j) {
            cout << path[j] << (j == (int)path.size() - 1 ? "" : " ");
        }
        cout << "\n";
    }

    return 0;
}