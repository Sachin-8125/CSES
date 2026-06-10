#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    long long sum;
    long long pref;
    long long suff;
    long long max_sub;
};

int n, q;
vector<long long> arr;
vector<Node> tree;

Node combine(const Node& left, const Node& right) {
    Node res;
    res.sum = left.sum + right.sum;
    res.pref = max(left.pref, left.sum + right.pref);
    res.suff = max(right.suff, right.sum + left.suff);
    res.max_sub = max({left.max_sub, right.max_sub, left.suff + right.pref});
    return res;
}

void build(int node, int start, int end) {
    if (start == end) {
        long long val = arr[start];
        tree[node] = {val, max(0LL, val), max(0LL, val), max(0LL, val)};
        return;
    }
    int mid = (start + end) / 2;
    build(2 * node, start, mid);
    build(2 * node + 1, mid + 1, end);
    tree[node] = combine(tree[2 * node], tree[2 * node + 1]);
}

Node query(int node, int start, int end, int l, int r) {
    if (r < start || end < l) {
        return {0, 0, 0, 0};
    }
    if (l <= start && end <= r) {
        return tree[node];
    }
    int mid = (start + end) / 2;
    Node left_res = query(2 * node, start, mid, l, r);
    Node right_res = query(2 * node + 1, mid + 1, end, l, r);
    return combine(left_res, right_res);
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
        int a, b;
        cin >> a >> b;
        Node ans = query(1, 1, n, a, b);
        cout << ans.max_sub << "\n";
    }
    
    return 0;
}