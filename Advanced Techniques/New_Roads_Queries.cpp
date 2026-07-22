#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int MAXN = 400005;
const int LOG = 19;

int parent[MAXN];
int tree_parent[MAXN];
int node_weight[MAXN];
int depth[MAXN];
int anc[MAXN][LOG];
vector<int> children[MAXN];

int find(int x) {
    if (parent[x] == x) return x;
    return parent[x] = find(parent[x]);
}

void dfs(int u, int d) {
    depth[u] = d;
    for (int j = 1; j < LOG; j++) {
        if (anc[u][j-1] != -1) {
            anc[u][j] = anc[anc[u][j-1]][j-1];
        }
    }
    for (int v : children[u]) {
        anc[v][0] = u;
        dfs(v, d + 1);
    }
}

int lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    int diff = depth[a] - depth[b];
    for (int j = 0; j < LOG; j++) {
        if ((diff >> j) & 1) a = anc[a][j];
    }
    if (a == b) return a;
    for (int j = LOG - 1; j >= 0; j--) {
        if (anc[a][j] != anc[b][j]) {
            a = anc[a][j];
            b = anc[b][j];
        }
    }
    return anc[a][0];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, q;
    cin >> n >> m >> q;
    
    int node_cnt = n + 1;
    
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        tree_parent[i] = -1;
    }
    
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        int ra = find(a), rb = find(b);
        if (ra != rb) {
            int new_node = node_cnt++;
            node_weight[new_node] = i;
            tree_parent[new_node] = -1;
            children[new_node].push_back(ra);
            children[new_node].push_back(rb);
            tree_parent[ra] = new_node;
            tree_parent[rb] = new_node;
            parent[ra] = new_node;
            parent[rb] = new_node;
            parent[new_node] = new_node;
        }
    }
    
    memset(anc, -1, sizeof(anc));
    
    for (int i = 1; i < node_cnt; i++) {
        if (tree_parent[i] == -1) {
            dfs(i, 0);
        }
    }
    
    while (q--) {
        int a, b;
        cin >> a >> b;
        
        if (a == b) {
            cout << 0 << "\n";
            continue;
        }
        
        int ra = find(a), rb = find(b);
        if (ra != rb) {
            cout << -1 << "\n";
        } else {
            int l = lca(a, b);
            cout << node_weight[l] << "\n";
        }
    }
    
    return 0;
}