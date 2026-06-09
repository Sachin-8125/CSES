#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 2e9;

int n, q;
vector<int> p;
vector<int> tree1, tree2;

void update(int node, int start, int end, int idx, int val) {
    if (start == end) {
        tree1[node] = val - start;
        tree2[node] = val + start;
        return;
    }
    int mid = (start + end) / 2;
    if (idx <= mid) {
        update(2 * node, start, mid, idx, val);
    } else {
        update(2 * node + 1, mid + 1, end, idx, val);
    }
    tree1[node] = min(tree1[2 * node], tree1[2 * node + 1]);
    tree2[node] = min(tree2[2 * node], tree2[2 * node + 1]);
}

int query(int node, int start, int end, int l, int r, int type) {
    if (r < start || end < l) {
        return INF;
    }
    if (l <= start && end <= r) {
        return (type == 1) ? tree1[node] : tree2[node];
    }
    int mid = (start + end) / 2;
    int p1 = query(2 * node, start, mid, l, r, type);
    int p2 = query(2 * node + 1, mid + 1, end, l, r, type);
    return min(p1, p2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> q)) return 0;

    p.resize(n + 1);
    tree1.resize(4 * (n + 1), INF);
    tree2.resize(4 * (n + 1), INF);

    for (int i = 1; i <= n; ++i) {
        cin >> p[i];
        update(1, 1, n, i, p[i]);
    }

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int k, x;
            cin >> k >> x;
            update(1, 1, n, k, x);
        } else {
            int k;
            cin >> k;
            int ans1 = query(1, 1, n, 1, k, 1) + k;
            int ans2 = query(1, 1, n, k, n, 2) - k;
            cout << min(ans1, ans2) << "\n";
        }
    }

    return 0;
}