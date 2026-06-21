#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    int n;
    vector<int> mn, mx, lazy;

    SegTree(int n = 0) { init(n); }

    void init(int n_) {
        n = n_;
        mn.assign(4 * n + 4, 0);
        mx.assign(4 * n + 4, 0);
        lazy.assign(4 * n + 4, 0);
    }

    void apply(int v, int val) {
        mn[v] += val;
        mx[v] += val;
        lazy[v] += val;
    }

    void push(int v) {
        if (lazy[v] != 0) {
            apply(v * 2, lazy[v]);
            apply(v * 2 + 1, lazy[v]);
            lazy[v] = 0;
        }
    }

    void pull(int v) {
        mn[v] = min(mn[v * 2], mn[v * 2 + 1]);
        mx[v] = max(mx[v * 2], mx[v * 2 + 1]);
    }

    void update(int v, int tl, int tr, int l, int r, int val) {
        if (l > r) return;
        if (l == tl && r == tr) {
            apply(v, val);
            return;
        }
        push(v);
        int tm = (tl + tr) / 2;
        update(v * 2, tl, tm, l, min(r, tm), val);
        update(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, val);
        pull(v);
    }

    // add val to every position in [l, r] (1-indexed)
    void update(int l, int r, int val) {
        update(1, 1, n, l, r, val);
    }

    int getMin() const { return mn[1]; }
    int getMax() const { return mx[1]; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    SegTree st(n);

    for (int i = 0; i < n; ++i) {
        int c, s;
        cin >> c >> s;
        if (s == 1)          // move to left stack
            st.update(1, c, +1);
        else                 // move to right stack
            st.update(1, c, -1);

        int mn = st.getMin();
        int mx = st.getMax();

        if (mx <= 0)        
            cout << "<\n";
        else if (mn >= 0)    
            cout << ">\n";
        else
            cout << "?\n";
    }
    return 0;
}