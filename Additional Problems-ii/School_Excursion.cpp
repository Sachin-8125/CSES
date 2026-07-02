#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

struct DSU {
    vector<int> parent;
    vector<int> size;

    DSU(int n) {
        parent.resize(n + 1);
        size.resize(n + 1, 1);
        for (int i = 1; i <= n; i++) {
            parent[i] = i;
        }
    }

    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }

    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            if (size[root_i] < size[root_j])
                swap(root_i, root_j);
            parent[root_j] = root_i;
            size[root_i] += size[root_j];
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    if (!(cin >> n >> m)) return 0;
    
    DSU dsu(n);
    
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        dsu.unite(u, v);
    }
    
    vector<int> freq(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        if (dsu.parent[i] == i) {
            freq[dsu.size[i]]++;
        }
    }
    
    bitset<100005> dp;
    dp[0] = 1;

    for (int w = 1; w <= n; w++) {
        if (freq[w] > 0) {
            int count = freq[w];
            for (int step = 1; count > 0; step <<= 1) {
                int take = min(step, count);
                dp |= (dp << (take * w));
                count -= take;
            }
        }
    }
    
    for (int i = 1; i <= n; i++) {
        cout << dp[i];
    }
    cout << "\n";
    
    return 0;
}