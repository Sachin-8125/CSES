#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

const int int_max_val = 2e5 + 5;
ll tree[4 * int_max_val];
ll lazy_add[4 * int_max_val];
ll lazy_set[4 * int_max_val];
bool has_set[4 * int_max_val]; 
ll a[int_max_val];

// Build the initial segment tree
void build(int node, int start, int end) {
    lazy_add[node] = 0;
    lazy_set[node] = 0;
    has_set[node] = false;
    if (start == end) {
        tree[node] = a[start];
        return;
    }
    int mid = (start + end) / 2;
    build(2 * node, start, mid);
    build(2 * node + 1, mid + 1, end);
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

void push(int node, int start, int end) {
    int mid = (start + end) / 2;
    
    if (has_set[node]) {
        // Apply to left child
        lazy_set[2 * node] = lazy_set[node];
        lazy_add[2 * node] = 0;
        has_set[2 * node] = true;
        tree[2 * node] = (mid - start + 1) * lazy_set[node];

        // Apply to right child
        lazy_set[2 * node + 1] = lazy_set[node];
        lazy_add[2 * node + 1] = 0;
        has_set[2 * node + 1] = true;
        tree[2 * node + 1] = (end - (mid + 1) + 1) * lazy_set[node];

        has_set[node] = false;
        lazy_set[node] = 0;
    }

    // Process add operations
    if (lazy_add[node] != 0) {
        // Apply to left child
        if (has_set[2 * node]) {
            lazy_set[2 * node] += lazy_add[node];
        } else {
            lazy_add[2 * node] += lazy_add[node];
        }
        tree[2 * node] += (mid - start + 1) * lazy_add[node];

        // Apply to right child
        if (has_set[2 * node + 1]) {
            lazy_set[2 * node + 1] += lazy_add[node];
        } else {
            lazy_add[2 * node + 1] += lazy_add[node];
        }
        tree[2 * node + 1] += (end - (mid + 1) + 1) * lazy_add[node];

        lazy_add[node] = 0;
    }
}

void update(int node, int start, int end, int l, int r, ll val, int type) {
    if (r < start || end < l) return;
    if (l <= start && end <= r) {
        if (type == 1) { // Range Add
            if (has_set[node]) {
                lazy_set[node] += val;
            } else {
                lazy_add[node] += val;
            }
            tree[node] += (end - start + 1) * val;
        } else { // Range Set
            lazy_set[node] = val;
            lazy_add[node] = 0;
            has_set[node] = true;
            tree[node] = (end - start + 1) * val;
        }
        return;
    }
    push(node, start, end);
    int mid = (start + end) / 2;
    update(2 * node, start, mid, l, r, val, type);
    update(2 * node + 1, mid + 1, end, l, r, val, type);
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

ll query(int node, int start, int end, int l, int r) {
    if (r < start || end < l) return 0;
    if (l <= start && end <= r) return tree[node];
    push(node, start, end);
    int mid = (start + end) / 2;
    return query(2 * node, start, mid, l, r) + query(2 * node + 1, mid + 1, end, l, r);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    build(1, 1, n);

    while (q--) {
        int type;
        cin >> type;
        if (type == 1 || type == 2) {
            int l, r;
            ll x;
            cin >> l >> r >> x;
            update(1, 1, n, l, r, x, type);
        } else if (type == 3) {
            int l, r;
            cin >> l >> r;
            cout << query(1, 1, n, l, r) << "\n";
        }
    }

    return 0;
}