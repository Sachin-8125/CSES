#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    long long sum;
    long long pref;
};

int n, q;
vector<long long> arr;
vector<Node> tree;

Node combine(Node left, Node right) {
    Node parent;
    parent.sum = left.sum + right.sum;
    parent.pref = max(left.pref, left.sum + right.pref);
    return parent;
}

// Build the Segment Tree
void build(int node, int start, int end) {
    if (start == end) {
        tree[node].sum = arr[start];
        tree[node].pref = max(0LL, arr[start]);
        return;
    }
    int mid = (start + end) / 2;
    build(2 * node, start, mid);
    build(2 * node + 1, mid + 1, end);
    tree[node] = combine(tree[2 * node], tree[2 * node + 1]);
}

void update(int node, int start, int end, int idx, long long val) {
    if (start == end) {
        tree[node].sum = val;
        tree[node].pref = max(0LL, val);
        return;
    }
    int mid = (start + end) / 2;
    if (idx <= mid) {
        update(2 * node, start, mid, idx, val);
    } else {
        update(2 * node + 1, mid + 1, end, idx, val);
    }
    tree[node] = combine(tree[2 * node], tree[2 * node + 1]);
}

Node query(int node, int start, int end, int L, int R) {
    if (L <= start && end <= R) {
        return tree[node];
    }
    int mid = (start + end) / 2;
    if (R <= mid) {
        return query(2 * node, start, mid, L, R);
    }
    if (L > mid) {
        return query(2 * node + 1, mid + 1, end, L, R);
    }
    Node left = query(2 * node, start, mid, L, R);
    Node right = query(2 * node + 1, mid + 1, end, L, R);
    return combine(left, right);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> q)) return 0;

    arr.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }

    tree.resize(4 * n + 1);
    build(1, 1, n);

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int k;
            long long u;
            cin >> k >> u;
            update(1, 1, n, k, u);
        } else if (type == 2) {
            int a, b;
            cin >> a >> b;
            Node result = query(1, 1, n, a, b);
            cout << result.pref << "\n";
        }
    }

    return 0;
}