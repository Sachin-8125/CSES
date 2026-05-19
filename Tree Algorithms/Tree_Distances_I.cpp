#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

vector<int> bfs(vector<vector<int>>& adj, int start) {
    int n = adj.size() - 1;
    vector<int> dist(n + 1, -1);
    queue<int> q;
    q.push(start);
    dist[start] = 0;
    
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        for (int neighbor : adj[node]) {
            if (dist[neighbor] == -1) {
                dist[neighbor] = dist[node] + 1;
                q.push(neighbor);
            }
        }
    }
    return dist;
}

int main() {
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    // Find one end of the diameter
    vector<int> dist1 = bfs(adj, 1);
    int end1 = max_element(dist1.begin() + 1, dist1.end()) - dist1.begin();
    
    // Find distances from end1
    vector<int> distFromEnd1 = bfs(adj, end1);
    
    // Find the other end of the diameter
    int end2 = max_element(distFromEnd1.begin() + 1, distFromEnd1.end()) - distFromEnd1.begin();
    
    // Find distances from end2
    vector<int> distFromEnd2 = bfs(adj, end2);
    
    // For each node, max distance is max(dist to end1, dist to end2)
    for (int i = 1; i <= n; i++) {
        cout << max(distFromEnd1[i], distFromEnd2[i]) << " ";
    }
    cout << endl;
    
    return 0;
}