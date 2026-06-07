#include <iostream>
#include <vector>

using namespace std;

struct FenwickTree {
    int n;
    vector<long long> tree;

    FenwickTree(int n) {
        this->n = n;
        tree.assign(n + 1, 0);
    }

    void add(int i, long long delta) {
        for (; i <= n; i += i & -i) {
            tree[i] += delta;
        }
    }

    long long query(int i) {
        long long sum = 0;
        for (; i > 0; i -= i & -i) {
            sum += tree[i];
        }
        return sum;
    }

    long long range_query(int l, int r) {
        return query(r) - query(l - 1);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    vector<long long> arr(n + 1);
    FenwickTree bit(n);

    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        bit.add(i, arr[i]);
    }

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int k;
            long long u;
            cin >> k >> u;
            
            long long diff = u - arr[k];
            arr[k] = u;
            bit.add(k, diff);
        } else if (type == 2) {
            int a, b;
            cin >> a >> b;
            
            cout << bit.range_query(a, b) << "\n";
        }
    }

    return 0;
}