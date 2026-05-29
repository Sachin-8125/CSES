#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Line {
    long long m, c;
    long long eval(long long x) const { 
        return m * x + c; 
    }
};

const int MAXN = 200005;
Line tree_arr[4 * MAXN];

void add_line(int node, int l, int r, Line nw) {
    int mid = l + (r - l) / 2;
    bool mid_better = nw.eval(mid) > tree_arr[node].eval(mid);
    
    if (mid_better) {
        swap(tree_arr[node], nw);
    }
    if (l == r) return;
    
    if (nw.eval(l) > tree_arr[node].eval(l)) {
        add_line(2 * node, l, mid, nw);
    } else if (nw.eval(r) > tree_arr[node].eval(r)) {
        add_line(2 * node + 1, mid + 1, r, nw);
    }
}

void add_segment(int node, int l, int r, int ql, int qr, Line nw) {
    if (ql <= l && r <= qr) {
        add_line(node, l, r, nw);
        return;
    }
    int mid = l + (r - l) / 2;
    if (ql <= mid) add_segment(2 * node, l, mid, ql, qr, nw);
    if (qr > mid) add_segment(2 * node + 1, mid + 1, r, ql, qr, nw);
}

long long query(int node, int l, int r, int x) {
    long long res = tree_arr[node].eval(x);
    if (l == r) return res;
    int mid = l + (r - l) / 2;
    if (x <= mid) res = max(res, query(2 * node, l, mid, x));
    else res = max(res, query(2 * node + 1, mid + 1, r, x));
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    if (!(cin >> n >> k)) return 0;
    
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    vector<int> L(n), R(n);
    vector<int> st;
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.back()] >= a[i]) {
            st.pop_back();
        }
        L[i] = st.empty() ? -1 : st.back();
        st.push_back(i);
    }
    
    st.clear();
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && a[st.back()] > a[i]) {
            st.pop_back();
        }
        R[i] = st.empty() ? n : st.back();
        st.push_back(i);
    }
    
    int M = n - k;
    for (int i = 0; i < n; i++) {
        long long l = L[i] + 1;
        long long r = R[i] - 1;
        long long val = a[i];
        
        long long L1 = max(0LL, l - k + 1);
        long long R1 = min((long long)M, min(l, r - k + 1));
        if (L1 <= R1) {
            add_segment(1, 0, M, L1, R1, {val, val * (k - l)});
        }
        
        long long L2 = max(0LL, min(l, r - k + 1));
        long long R2 = min((long long)M, max(l, r - k + 1));
        if (L2 <= R2) {
            add_segment(1, 0, M, L2, R2, {0, val * min((long long)k, r - l + 1)});
        }
        
        long long L3 = max(0LL, max(l, r - k + 1));
        long long R3 = min((long long)M, r);
        if (L3 <= R3) {
            add_segment(1, 0, M, L3, R3, {-val, val * (r + 1LL)});
        }
    }
    
    for (int x = 0; x <= M; x++) {
        cout << query(1, 0, M, x) << (x == M ? "" : " ");
    }
    cout << "\n";
    
    return 0;
}