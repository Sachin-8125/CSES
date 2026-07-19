#include <iostream>
#include <vector>
using namespace std;

struct DSU {
    vector<int> parent, sz;
    DSU(int n) {
        parent.resize(n + 1);
        sz.assign(n + 1, 1);
        for (int i = 1; i <= n; i++) parent[i] = i;
    }
    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }
    int unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return sz[a];
        if (sz[a] < sz[b]) swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
        return sz[a];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    DSU dsu(n);
    int components = n;
    int largest = 1;

    while (m--) {
        int a, b;
        cin >> a >> b;
        int ra = dsu.find(a), rb = dsu.find(b);
        if (ra != rb) {
            int newSize = dsu.unite(ra, rb);
            components--;
            if (newSize > largest) largest = newSize;
        }
        cout << components << " " << largest << "\n";
    }

    return 0;
}