#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    long long sum;
    long long pref;
    long long suff;
    long long ans;
};

int n, m;
vector<long long> arr;
vector<Node> tree;

Node combine(Node left, Node right) {
    Node parent;
    parent.sum = left.sum + right.sum;
    parent.pref = max(left.pref, left.sum + right.pref);
    parent.suff = max(right.suff, right.sum + left.suff);
    parent.ans = max({left.ans, right.ans, left.suff + right.pref});
    return parent;
}

Node make_node(long long val) {
    Node node;
    node.sum = val;
    node.pref = max(0LL, val);
    node.suff = max(0LL, val);
    node.ans = max(0LL, val);
    return node;
}

void build(int node, int start, int end) {
    if (start == end) {
        tree[node] = make_node(arr[start]);
        return;
    }
    int mid = (start + end) / 2;
    build(2 * node, start, mid);
    build(2 * node + 1, mid + 1, end);
    tree[node] = combine(tree[2 * node], tree[2 * node + 1]);
}

void update(int node, int start, int end, int idx, long long val) {
    if (start == end) {
        tree[node] = make_node(val);
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> m)) return 0;

    arr.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }

    tree.resize(4 * n + 1);
    build(1, 1, n);

    for (int i = 0; i < m; i++) {
        int k;
        long long x;
        cin >> k >> x;
        update(1, 1, n, k, x);
        cout << tree[1].ans << "\n";
    }

    return 0;
}