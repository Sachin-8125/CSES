#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct SegTree {
    int n;
    vector<long long> tree;
    SegTree(int n) : n(n) { tree.assign(4 * n, 0); }
    void build(int node, int start, int end, const vector<long long>& a) {
        if (start == end) {
            tree[node] = a[start];
            return;
        }
        int mid = (start + end) / 2;
        build(2 * node, start, mid, a);
        build(2 * node + 1, mid + 1, end, a);
        tree[node] = min(tree[2 * node], tree[2 * node + 1]);
    }
    void update(int node, int start, int end, int idx, long long val) {
        if (start == end) {
            tree[node] = val;
            return;
        }
        int mid = (start + end) / 2;
        if (idx <= mid) update(2 * node, start, mid, idx, val);
        else update(2 * node + 1, mid + 1, end, idx, val);
        tree[node] = min(tree[2 * node], tree[2 * node + 1]);
    }
    long long query() { return tree[1]; }
};

struct MaxElement {
    long long mx, mn;
    int i;
    bool operator<(const MaxElement& other) const {
        if (mx != other.mx) return mx < other.mx;
        return mn < other.mn; 
    }
};

struct MinElement {
    long long next_mn;
    int i;
    bool operator<(const MinElement& other) const {
        return next_mn < other.next_mn; 
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    SegTree st_V(n);
    st_V.build(1, 0, n - 1, a);

    priority_queue<MaxElement> pq;
    for(int i = 0; i < n; ++i) {
        pq.push({a[i], a[i], i});
    }

    vector<long long> Y(m + 1), V(m + 1);
    Y[0] = pq.top().mx;
    V[0] = st_V.query();

    vector<long long> c(n, 1);
    for (int j = 1; j <= m; ++j) {
        MaxElement top = pq.top();
        pq.pop();
        int i = top.i;
        c[i]++;
        long long new_mx = (a[i] + c[i] - 1) / c[i];
        long long new_mn = a[i] / c[i];
        
        st_V.update(1, 0, n - 1, i, new_mn);
        pq.push({new_mx, new_mn, i});
        
        Y[j] = pq.top().mx;
        V[j] = st_V.query();
    }

    SegTree st_X(n);
    st_X.build(1, 0, n - 1, a);

    priority_queue<MinElement> pq_min;
    for(int i = 0; i < n; ++i) {
        pq_min.push({a[i] / 2, i});
    }

    vector<long long> X_opt(m + 1);
    X_opt[0] = st_X.query();

    vector<long long> c_min(n, 1);
    for (int k = 1; k <= m; ++k) {
        MinElement top = pq_min.top();
        pq_min.pop();
        int i = top.i;
        c_min[i]++;
        long long new_mn = a[i] / c_min[i];
        
        st_X.update(1, 0, n - 1, i, new_mn);
        pq_min.push({a[i] / (c_min[i] + 1), i});
        
        X_opt[k] = st_X.query();
    }

    vector<long long> diff(m + 1);
    for (int j = 0; j <= m; ++j) diff[j] = Y[j] - V[j];

    int LOG = 0;
    while ((1 << LOG) <= m + 1) LOG++;
    vector<vector<long long>> st_diff(LOG, vector<long long>(m + 1));
    for (int j = 0; j <= m; ++j) st_diff[0][j] = diff[j];

    for (int i = 1; i < LOG; ++i) {
        for (int j = 0; j + (1 << i) - 1 <= m; ++j) {
            st_diff[i][j] = min(st_diff[i-1][j], st_diff[i-1][j + (1 << (i-1))]);
        }
    }

    auto query_rmq = [&](int L, int R) {
        if (L > R) return (long long)2e18;
        int len = R - L + 1;
        int bitK = 31 - __builtin_clz(len);
        return min(st_diff[bitK][L], st_diff[bitK][R - (1 << bitK) + 1]);
    };

    for (int k = 1; k <= m; ++k) {
        long long X = X_opt[k];
        int low = 0, high = k, p = -1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (V[mid] >= X) {
                p = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        
        long long ans = 2e18;
        if (p != -1) ans = min(ans, Y[p] - X);     
        if (p < k) ans = min(ans, query_rmq(p + 1, k)); 
        
        cout << ans << (k == m ? "" : " ");
    }
    cout << "\n";

    return 0;
}