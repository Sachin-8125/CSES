#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 200005;
long long x[MAXN];
long long tree_max[4 * MAXN];
long long tree_sum[4 * MAXN];
long long orig_sum[4 * MAXN];

long long get_modified_sum(int node, int start, int end, long long val) {
    if (start == end) {
        return max(val, tree_max[node]);
    }
    int mid = (start + end) / 2;
    if (val >= tree_max[2 * node]) {
        return val * (mid - start + 1) + get_modified_sum(2 * node + 1, mid + 1, end, val);
    } else {
        return get_modified_sum(2 * node, start, mid, val) + (tree_sum[node] - tree_sum[2 * node]);
    }
}

void build(int node, int start, int end) {
    if (start == end) {
        tree_max[node] = x[start];
        tree_sum[node] = x[start];
        orig_sum[node] = x[start];
        return;
    }
    int mid = (start + end) / 2;
    build(2 * node, start, mid);
    build(2 * node + 1, mid + 1, end);
    
    tree_max[node] = max(tree_max[2 * node], tree_max[2 * node + 1]);
    orig_sum[node] = orig_sum[2 * node] + orig_sum[2 * node + 1];
    tree_sum[node] = tree_sum[2 * node] + get_modified_sum(2 * node + 1, mid + 1, end, tree_max[2 * node]);
}

pair<long long, long long> query(int node, int start, int end, int l, int r, long long running_max) {
    if (l <= start && end <= r) {
        long long current_sum = get_modified_sum(node, start, end, running_max);
        long long new_max = max(running_max, tree_max[node]);
        return {current_sum, new_max};
    }
    int mid = (start + end) / 2;
    if (r <= mid) {
        return query(2 * node, start, mid, l, r, running_max);
    } else if (l > mid) {
        return query(2 * node + 1, mid + 1, end, l, r, running_max);
    } else {
        auto left_res = query(2 * node, start, mid, l, mid, running_max);
        auto right_res = query(2 * node + 1, mid + 1, end, mid + 1, r, left_res.second);
        return {left_res.first + right_res.first, right_res.second};
    }
}

long long query_orig_sum(int node, int start, int end, int l, int r) {
    if (l <= start && end <= r) {
        return orig_sum[node];
    }
    int mid = (start + end) / 2;
    long long sum = 0;
    if (l <= mid) sum += query_orig_sum(2 * node, start, mid, l, r);
    if (r > mid) sum += query_orig_sum(2 * node + 1, mid + 1, end, l, r);
    return sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q;
    if (!(cin >> n >> q)) return 0;
    
    for (int i = 1; i <= n; ++i) {
        cin >> x[i];
    }
    
    build(1, 1, n);
    
    while (q--) {
        int a, b;
        cin >> a >> b;
        
        auto result = query(1, 1, n, a, b, 0);
        long long actual_sum = query_orig_sum(1, 1, n, a, b);
        
        cout << result.first - actual_sum << "\n";
    }
    
    return 0;
}