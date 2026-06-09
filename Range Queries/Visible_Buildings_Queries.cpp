#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    int max_val;
    int visible;
};

int n, q;
vector<int> h;
vector<Node> tree;

int count_visible(int node, int start, int end, int limit) {
    if (tree[node].max_val <= limit) {
        return 0;
    }
    if (start == end) {
        return tree[node].max_val > limit ? 1 : 0;
    }
    
    int mid = (start + end) / 2;
    int left_child = 2 * node;
    int right_child = 2 * node + 1;
    
    if (tree[left_child].max_val <= limit) {
        return count_visible(right_child, mid + 1, end, limit);
    }
    
    return count_visible(left_child, start, mid, limit) + (tree[node].visible - tree[left_child].visible);
}

void build(int node, int start, int end) {
    if (start == end) {
        tree[node] = {h[start], 1};
        return;
    }
    int mid = (start + end) / 2;
    build(2 * node, start, mid);
    build(2 * node + 1, mid + 1, end);
    
    tree[node].max_val = max(tree[2 * node].max_val, tree[2 * node + 1].max_val);
    tree[node].visible = tree[2 * node].visible + count_visible(2 * node + 1, mid + 1, end, tree[2 * node].max_val);
}

pair<int, int> query(int node, int start, int end, int l, int r, int current_max) {
    if (r < start || end < l) {
        return {0, 0};
    }
    if (l <= start && end <= r) {
        int count = count_visible(node, start, end, current_max);
        return {count, tree[node].max_val};
    }
    
    int mid = (start + end) / 2;
    auto left_res = query(2 * node, start, mid, l, r, current_max);
    
    current_max = max(current_max, left_res.second);
    
    auto right_res = query(2 * node + 1, mid + 1, end, l, r, current_max);
    
    return {left_res.first + right_res.first, max(left_res.second, right_res.second)};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    if (!(cin >> n >> q)) return 0;
    
    h.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }
    
    tree.resize(4 * n + 1);
    build(1, 1, n);
    
    while (q--) {
        int a, b;
        cin >> a >> b;
        auto ans = query(1, 1, n, a, b, 0);
        cout << ans.first << "\n";
    }
    
    return 0;
}