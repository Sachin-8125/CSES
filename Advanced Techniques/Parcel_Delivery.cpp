#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const long long INF = 1e18;

struct Edge {
    int to, cap, cost, flow;
};

vector<Edge> edges;
vector<vector<int>> adj;

void addEdge(int from, int to, int cap, int cost) {
    adj[from].push_back(edges.size());
    edges.push_back({to, cap, cost, 0});
    adj[to].push_back(edges.size());
    edges.push_back({from, 0, -cost, 0});
}

pair<long long, long long> minCostFlow(int s, int t, int maxFlow, int numNodes) {
    long long totalFlow = 0, totalCost = 0;
    
    while (totalFlow < maxFlow) {
        vector<long long> dist(numNodes + 1, INF);
        vector<int> parent(numNodes + 1, -1);
        vector<int> parentEdge(numNodes + 1, -1);
        vector<bool> inQueue(numNodes + 1, false);
        
        dist[s] = 0;
        queue<int> q;
        q.push(s);
        inQueue[s] = true;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            inQueue[u] = false;
            
            for (int id : adj[u]) {
                if (edges[id].cap - edges[id].flow > 0 && dist[u] + edges[id].cost < dist[edges[id].to]) {
                    dist[edges[id].to] = dist[u] + edges[id].cost;
                    parent[edges[id].to] = u;
                    parentEdge[edges[id].to] = id;
                    if (!inQueue[edges[id].to]) {
                        q.push(edges[id].to);
                        inQueue[edges[id].to] = true;
                    }
                }
            }
        }
        
        if (dist[t] == INF) break;
        
        long long pushFlow = maxFlow - totalFlow;
        for (int v = t; v != s; v = parent[v])
            pushFlow = min(pushFlow, (long long)(edges[parentEdge[v]].cap - edges[parentEdge[v]].flow));
        
        for (int v = t; v != s; v = parent[v]) {
            edges[parentEdge[v]].flow += pushFlow;
            edges[parentEdge[v] ^ 1].flow -= pushFlow;
        }
        
        totalFlow += pushFlow;
        totalCost += pushFlow * dist[t];
    }
    
    return make_pair(totalFlow, totalCost);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, k;
    cin >> n >> m >> k;
    adj.resize(n + 1);
    
    for (int i = 0; i < m; i++) {
        int a, b, r, c;
        cin >> a >> b >> r >> c;
        addEdge(a, b, r, c);
    }
    
    pair<long long, long long> result = minCostFlow(1, n, k, n);
    
    if (result.first < k) cout << -1 << "\n";
    else cout << result.second << "\n";
    
    return 0;
}