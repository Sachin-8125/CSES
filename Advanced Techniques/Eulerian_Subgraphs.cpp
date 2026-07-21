#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;

struct DSU {
    vector<int> parent;
    vector<int> sz;
    int comps;
    DSU(int n) {
        parent.resize(n + 1);
        sz.resize(n + 1, 1);
        for(int i = 1; i <= n; ++i) parent[i] = i;
        comps = n;
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
            if (sz[root_i] < sz[root_j]) swap(root_i, root_j);
            parent[root_j] = root_i;
            sz[root_i] += sz[root_j];
            comps--;
        }
    }
};

long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    DSU dsu(n);
    for(int i = 0; i < m; ++i){
        int u, v;
        cin >> u >> v;
        dsu.unite(u, v);
    }

    long long ans = power(2, m - n + dsu.comps);
    cout << ans << "\n";

    return 0;
}