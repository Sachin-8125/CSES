#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1e9;

struct Edge {
    int to, cap, cost, rev;
};

vector<vector<Edge>> adj;
vector<int> dist_arr, parent_node, parent_edge;

void add_edge(int from, int to, int cap, int cost) {
    adj[from].push_back({to, cap, cost, (int)adj[to].size()});
    adj[to].push_back({from, 0, -cost, (int)adj[from].size() - 1});
}

bool spfa(int s, int t, int nodes_count) {
    dist_arr.assign(nodes_count, INF);
    parent_node.assign(nodes_count, -1);
    parent_edge.assign(nodes_count, -1);
    vector<bool> in_queue(nodes_count, false);
    queue<int> q;

    dist_arr[s] = 0;
    q.push(s);
    in_queue[s] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        in_queue[u] = false;

        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i].to;
            int cap = adj[u][i].cap;
            int cost = adj[u][i].cost;

            if (cap > 0 && dist_arr[v] > dist_arr[u] + cost) {
                dist_arr[v] = dist_arr[u] + cost;
                parent_node[v] = u;
                parent_edge[v] = i;
                if (!in_queue[v]) {
                    q.push(v);
                    in_queue[v] = true;
                }
            }
        }
    }
    return dist_arr[t] != INF;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    int sumA = 0, sumB = 0;
    vector<int> a(n), b(n);

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        sumA += a[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
        sumB += b[i];
    }

    if (sumA != sumB) {
        cout << -1 << "\n";
        return 0;
    }

    int source = 0, sink = 2 * n + 1;
    int total_nodes = 2 * n + 2;
    adj.assign(total_nodes, vector<Edge>());

    for (int i = 0; i < n; ++i) {
        add_edge(source, i + 1, a[i], 0);
    }
    for (int j = 0; j < n; ++j) {
        add_edge(n + 1 + j, sink, b[j], 0);
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int cost;
            cin >> cost;
            add_edge(i + 1, n + 1 + j, 1, -cost); 
        }
    }

    int flow = 0;
    int max_coins = 0;

    while (spfa(source, sink, total_nodes)) {
        int push = INF;
        int curr = sink;
        
        while (curr != source) {
            int p = parent_node[curr];
            int idx = parent_edge[curr];
            push = min(push, adj[p][idx].cap);
            curr = p;
        }

        flow += push;
        max_coins += push * dist_arr[sink];

        curr = sink;
        while (curr != source) {
            int p = parent_node[curr];
            int idx = parent_edge[curr];
            int rev_idx = adj[p][idx].rev;

            adj[p][idx].cap -= push;
            adj[curr][rev_idx].cap += push;
            curr = p;
        }
    }

    if (flow != sumA) {
        cout << -1 << "\n";
        return 0;
    }

    cout << -max_coins << "\n";

    vector<string> grid(n, string(n, '.'));
    for (int i = 0; i < n; ++i) {
        int u = i + 1;
        for (const auto& edge : adj[u]) {
            int v = edge.to;
            if (v >= n + 1 && v <= 2 * n && edge.cap == 0) {
                grid[i][v - n - 1] = 'X';
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << grid[i] << "\n";
    }

    return 0;
}