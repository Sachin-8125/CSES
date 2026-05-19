#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 200005;
vector<int> adj[MAXN];
int maxNode, maxDist;

void dfs(int node, int parent, int dist) {
    if (dist > maxDist) {
        maxDist = dist;
        maxNode = node;
    }
    
    for (int neighbor : adj[node]) {
        if (neighbor != parent) {
            dfs(neighbor, node, dist + 1);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    maxDist = -1;
    maxNode = 1;
    dfs(1, 0, 0);
    
    int startNode = maxNode;
    maxDist = -1;
    dfs(startNode, 0, 0);
    
    cout << maxDist << endl;
    
    return 0;
}