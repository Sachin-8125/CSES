#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long INF = 4e18;
const int MAX_X = 100000;

struct Line {
    long long a, b;
    bool is_null;
    long long eval(long long x) const {
        if (is_null) return -INF;
        return a * x + b;
    }
};

struct LiChaoNode {
    Line line = {0, 0, true};
    int left = -1, right = -1;
};

vector<LiChaoNode> lc_tree;

int get_new_node() {
    lc_tree.push_back(LiChaoNode());
    return lc_tree.size() - 1;
}

void lc_insert(int node, int l, int r, Line new_line) {
    int mid = l + (r - l) / 2;
    bool b_l = new_line.eval(l) > lc_tree[node].line.eval(l);
    bool b_m = new_line.eval(mid) > lc_tree[node].line.eval(mid);

    if (b_m) {
        swap(lc_tree[node].line, new_line);
    }

    if (l == r || new_line.is_null) return;

    if (b_l != b_m) {
        if (lc_tree[node].left == -1) lc_tree[node].left = get_new_node();
        lc_insert(lc_tree[node].left, l, mid, new_line);
    } else {
        if (lc_tree[node].right == -1) lc_tree[node].right = get_new_node();
        lc_insert(lc_tree[node].right, mid + 1, r, new_line);
    }
}

long long lc_query(int node, int l, int r, int x) {
    if (node == -1) return -INF;
    long long res = lc_tree[node].line.eval(x);
    if (l == r) return res;
    int mid = l + (r - l) / 2;
    if (x <= mid) {
        res = max(res, lc_query(lc_tree[node].left, l, mid, x));
    } else {
        res = max(res, lc_query(lc_tree[node].right, mid + 1, r, x));
    }
    return res;
}

int seg_tree[4 * (MAX_X + 1)];

void seg_insert(int node, int start, int end, int l, int r, Line line) {
    if (r < start || end < l) return;
    if (l <= start && end <= r) {
        lc_insert(seg_tree[node], 0, MAX_X, line);
        return;
    }
    int mid = start + (end - start) / 2;
    seg_insert(2 * node, start, mid, l, r, line);
    seg_insert(2 * node + 1, mid + 1, end, l, r, line);
}

long long seg_query(int node, int start, int end, int x) {
    long long res = lc_query(seg_tree[node], 0, MAX_X, x);
    if (start == end) return res;
    int mid = start + (end - start) / 2;
    if (x <= mid) {
        res = max(res, seg_query(2 * node, start, mid, x));
    } else {
        res = max(res, seg_query(2 * node + 1, mid + 1, end, x));
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    for (int i = 0; i < 4 * (MAX_X + 1); ++i) {
        seg_tree[i] = get_new_node();
    }

    while (n--) {
        int type;
        cin >> type;
        if (type == 1) {
            long long a, b;
            int l, r;
            cin >> a >> b >> l >> r;
            seg_insert(1, 0, MAX_X, l, r, {a, b, false});
        } else {
            int x;
            cin >> x;
            long long ans = seg_query(1, 0, MAX_X, x);
            if (ans <= -INF / 2) {
                cout << "NO\n";
            } else {
                cout << ans << "\n";
            }
        }
    }

    return 0;
}