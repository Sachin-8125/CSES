#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Line {
    long long m_slope;
    long long c_intercept;

    long long eval(long long x) const {
        return m_slope * x + c_intercept;
    }
};

class LiChaoTree {
private:
    int sz;
    vector<Line> tree;
    const Line line_inf = {0, -1000000000000000000LL};

public:
    LiChaoTree(int m) {
        sz = m + 1;
        tree.resize(4 * sz, line_inf);
    }

    void insert(int node, int l, int r, Line new_line) {
        int mid = l + (r - l) / 2;
        bool b_l = new_line.eval(l) > tree[node].eval(l);
        bool b_mid = new_line.eval(mid) > tree[node].eval(mid);

        if (b_mid) {
            swap(tree[node], new_line);
        }

        if (l == r) return;

        if (b_l != b_mid) {
            insert(2 * node, l, mid, new_line);
        } else {
            insert(2 * node + 1, mid + 1, r, new_line);
        }
    }

    long long query(int node, int l, int r, int x) {
        long long res = tree[node].eval(x);
        if (l == r) return res;

        int mid = l + (r - l) / 2;
        if (x <= mid) {
            return max(res, query(2 * node, l, mid, x));
        } else {
            return max(res, query(2 * node + 1, mid + 1, r, x));
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    LiChaoTree lc(m);

    for (int i = 0; i < n; ++i) {
        long long y1, y2;
        cin >> y1 >> y2;
        
        long long slope = (y2 - y1) / m;
        long long intercept = y1;
        
        lc.insert(1, 0, m, {slope, intercept});
    }

    for (int x = 0; x <= m; ++x) {
        cout << lc.query(1, 0, m, x) << (x == m ? "" : " ");
    }
    cout << "\n";

    return 0;
}