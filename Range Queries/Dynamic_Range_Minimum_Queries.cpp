#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9 + 7;

struct SegmentTree {
    int n;
    vector<int> tree;

    SegmentTree(int n) {
        this->n = n;
        tree.assign(4 * n, INF);
    }

    void build(const vector<int>& a, int v, int tl, int tr) {
        if (tl == tr) {
            tree[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, v * 2, tl, tm);
            build(a, v * 2 + 1, tm + 1, tr);
            tree[v] = min(tree[v * 2], tree[v * 2 + 1]);
        }
    }

    void update(int v, int tl, int tr, int pos, int new_val) {
        if (tl == tr) {
            tree[v] = new_val;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(v * 2, tl, tm, pos, new_val);
            else
                update(v * 2 + 1, tm + 1, tr, pos, new_val);
            tree[v] = min(tree[v * 2], tree[v * 2 + 1]);
        }
    }

    int query(int v, int tl, int tr, int l, int r) {
        if (l > r) 
            return INF;
        if (l == tl && r == tr) {
            return tree[v];
        }
        int tm = (tl + tr) / 2;
        return min(query(v * 2, tl, tm, l, min(r, tm)),
                   query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    SegmentTree st(n);
    st.build(a, 1, 1, n);

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int k, u;
            cin >> k >> u;
            st.update(1, 1, n, k, u);
        } else if (type == 2) {
            int a_idx, b_idx;
            cin >> a_idx >> b_idx;
            cout << st.query(1, 1, n, a_idx, b_idx) << "\n";
        }
    }

    return 0;
}