#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 200005;
const long long INF = 1e18;

struct Node {
    int left_child, right_child;
    long long sum;
} tree[MAXN * 40];

int nodes_cnt = 0;
int roots[MAXN];
vector<long long> coord;

int get_coord_idx(long long val) {
    return lower_bound(coord.begin(), coord.end(), val) - coord.begin();
}

int update(int prev_node, int start, int end, int val_idx, long long actual_val) {
    int current_node = ++nodes_cnt;
    tree[current_node] = tree[prev_node];
    tree[current_node].sum += actual_val;
    
    if (start == end) {
        return current_node;
    }
    
    int mid = (start + end) / 2;
    if (val_idx <= mid) {
        tree[current_node].left_child = update(tree[prev_node].left_child, start, mid, val_idx, actual_val);
    } else {
        tree[current_node].right_child = update(tree[prev_node].right_child, mid + 1, end, val_idx, actual_val);
    }
    return current_node;
}

long long query(int left_node, int right_node, int start, int end, int max_idx) {
    if (max_idx < start || left_node == right_node) return 0;
    if (end <= max_idx) {
        return tree[right_node].sum - tree[left_node].sum;
    }
    
    int mid = (start + end) / 2;
    long long left_sum = query(tree[left_node].left_child, tree[right_node].left_child, start, mid, max_idx);
    long long right_sum = 0;
    if (max_idx > mid) {
        right_sum = query(tree[left_node].right_child, tree[right_node].right_child, mid + 1, end, max_idx);
    }
    return left_sum + right_sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q;
    if (!(cin >> n >> q)) return 0;
    
    vector<long long> x(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> x[i];
        coord.push_back(x[i]);
    }
    
    sort(coord.begin(), coord.end());
    coord.erase(unique(coord.begin(), coord.end()), coord.end());
    int coord_size = coord.size();
    
    roots[0] = 0;
    for (int i = 1; i <= n; i++) {
        int comp_idx = get_coord_idx(x[i]);
        roots[i] = update(roots[i - 1], 0, coord_size - 1, comp_idx, x[i]);
    }
    
    while (q--) {
        int a, b;
        cin >> a >> b;
        
        long long current_target = 1;
        while (true) {
            auto it = upper_bound(coord.begin(), coord.end(), current_target);
            int max_idx = distance(coord.begin(), it) - 1;
            
            if (max_idx < 0) {
                break;
            }
            
            long long extended_sum = query(roots[a - 1], roots[b], 0, coord_size - 1, max_idx);
            
            if (extended_sum < current_target) {
                break;
            }
            current_target = extended_sum + 1;
        }
        cout << current_target << "\n";
    }
    
    return 0;
}