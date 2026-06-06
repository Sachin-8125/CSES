#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Line {
    long long m, c;
    long long eval(long long x) {
        return m * x + c;
    }
};

const long long INF = -2e18;
const int MAXM = 100005;

Line tree[4 * MAXM];

void init(int node, int l, int r) {
    tree[node] = {0, INF};
    if (l == r) return;
    int mid = (l + r) / 2;
    init(2 * node, l, mid);
    init(2 * node + 1, mid + 1, r);
}

void insert_segment(int node, int l, int r, int ql, int qr, Line new_line) {
    if (ql > r || qr < l) return;
    
    int mid = (l + r) / 2;
    
    if (ql <= l && r <= qr) {
        bool b_l = new_line.eval(l) > tree[node].eval(l);
        bool b_mid = new_line.eval(mid) > tree[node].eval(mid);
        
        if (b_mid) {
            swap(tree[node], new_line);
        }
        
        if (l == r) return;
        
        if (b_l != b_mid) {
            insert_segment(2 * node, l, mid, ql, qr, new_line);
        } else {
            insert_segment(2 * node + 1, mid + 1, r, ql, qr, new_line);
        }
        return;
    }
    
    insert_segment(2 * node, l, mid, ql, qr, new_line);
    insert_segment(2 * node + 1, mid + 1, r, ql, qr, new_line);
}

long long query(int node, int l, int r, int x) {
    long long res = tree[node].eval(x);
    if (l == r) return res;
    
    int mid = (l + r) / 2;
    if (x <= mid) {
        return max(res, query(2 * node, l, mid, x));
    } else {
        return max(res, query(2 * node + 1, mid + 1, r, x));
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    if (!(cin >> n >> m)) return 0;
    
    init(1, 0, m);
    
    for (int i = 0; i < n; ++i) {
        long long x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        
        if (x1 > x2) {
            swap(x1, x2);
            swap(y1, y2);
        }
        
        long long slope = (y2 - y1) / (x2 - x1);
        long long intercept = y1 - slope * x1;
        
        Line line = {slope, intercept};
        insert_segment(1, 0, m, x1, x2, line);
    }
    
    for (int x = 0; x <= m; ++x) {
        long long ans = query(1, 0, m, x);
        if (ans <= -1e18) {
            cout << -1 << (x == m ? "" : " ");
        } else {
            cout << ans << (x == m ? "" : " ");
        }
    }
    cout << "\n";
    
    return 0;
}