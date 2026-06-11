#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 200005;

struct Node {
    long long sum;
    long long lazy_linear;
    long long lazy_const;
};

int n, q;
long long arr[MAXN];
Node tree[4 * MAXN];

// Helper to calculate the sum of indices from l to r
long long sum_indices(long long l, long long r) {
    return (r * (r + 1) / 2) - (l * (l - 1) / 2);
}

void build(int node, int start, int end) {
    tree[node].lazy_linear = 0;
    tree[node].lazy_const = 0;
    if (start == end) {
        tree[node].sum = arr[start];
        return;
    }
    int mid = (start + end) / 2;
    build(2 * node, start, mid);
    build(2 * node + 1, mid + 1, end);
    tree[node].sum = tree[2 * node].sum + tree[2 * node + 1].sum;
}

void push(int node, int start, int end) {
    if (tree[node].lazy_linear == 0 && tree[node].lazy_const == 0) return;

    long long lin = tree[node].lazy_linear;
    long long con = tree[node].lazy_const;

    int mid = (start + end) / 2;

    // Apply to left child
    tree[2 * node].sum += lin * sum_indices(start, mid) + con * (mid - start + 1);
    tree[2 * node].lazy_linear += lin;
    tree[2 * node].lazy_const += con;

    // Apply to right child
    tree[2 * node + 1].sum += lin * sum_indices(mid + 1, end) + con * (end - mid);
    tree[2 * node + 1].lazy_linear += lin;
    tree[2 * node + 1].lazy_const += con;

    // Clear current node lazy values
    tree[node].lazy_linear = 0;
    tree[node].lazy_const = 0;
}

void update(int node, int start, int end, int l, int r, long long lin_val, long long con_val) {
    if (r < start || end < l) return;

    if (l <= start && end <= r) {
        tree[node].sum += lin_val * sum_indices(start, end) + con_val * (end - start + 1);
        tree[node].lazy_linear += lin_val;
        tree[node].lazy_const += con_val;
        return;
    }

    push(node, start, end);
    int mid = (start + end) / 2;
    update(2 * node, start, mid, l, r, lin_val, con_val);
    update(2 * node + 1, mid + 1, end, l, r, lin_val, con_val);
    tree[node].sum = tree[2 * node].sum + tree[2 * node + 1].sum;
}

long long query(int node, int start, int end, int l, int r) {
    if (r < start || end < l) return 0;
    if (l <= start && end <= r) return tree[node].sum;

    push(node, start, end);
    int mid = (start + end) / 2;
    long long p1 = query(2 * node, start, mid, l, r);
    long long p2 = query(2 * node + 1, mid + 1, end, l, r);
    return p1 + p2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> q)) return 0;

    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }

    build(1, 1, n);

    while (q--) {
        int type, a, b;
        cin >> type >> a >> b;
        if (type == 1) {
            // update linear factor = 1, constant factor = 1 - a
            update(1, 1, n, a, b, 1, 1 - a);
        } else {
            cout << query(1, 1, n, a, b) << "\n";
        }
    }

    return 0;
}
