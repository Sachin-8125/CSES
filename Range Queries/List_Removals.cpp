#include <iostream>
#include <vector>

using namespace std;

class SegmentTree {
    int n;
    vector<int> tree;

public:
    SegmentTree(int size) {
        n = size;
        tree.assign(4 * n, 0);
        build(1, 1, n);
    }

    void build(int node, int start, int end) {
        if (start == end) {
            tree[node] = 1;
            return;
        }
        int mid = start + (end - start) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    int find_and_remove(int node, int start, int end, int k) {
        if (start == end) {
            tree[node] = 0;
            return start;
        }
        
        int mid = start + (end - start) / 2;
        int original_idx;
        
        if (tree[2 * node] >= k) {
            original_idx = find_and_remove(2 * node, start, mid, k);
        } else {
            original_idx = find_and_remove(2 * node + 1, mid + 1, end, k - tree[2 * node]);
        }
        
        tree[node] = tree[2 * node] + tree[2 * node + 1];
        return original_idx;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> x(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> x[i];
    }

    SegmentTree st(n);

    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        int actual_idx = st.find_and_remove(1, 1, n, p);
        cout << x[actual_idx] << (i == n - 1 ? "" : " ");
    }
    cout << "\n";

    return 0;
}