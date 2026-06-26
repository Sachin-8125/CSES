#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct FenwickTree {
    int n;
    vector<int> tree;
    
    FenwickTree(int n) : n(n), tree(n + 1, 0) {}
    
    void add(int i, int delta) {
        for (; i <= n; i += i & -i) {
            tree[i] += delta;
        }
    }
    
    int query(int i) {
        int sum = 0;
        for (; i > 0; i -= i & -i) {
            sum += tree[i];
        }
        return sum;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> x(n);
    vector<int> values(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
        values[i] = x[i];
    }

    sort(values.begin(), values.end());
    
    FenwickTree bit(n);
    long long total_moves = 0;

    for (int i = 0; i < n; ++i) {
        int rank = lower_bound(values.begin(), values.end(), x[i]) - values.begin();
        
        int total_greater = n - 1 - rank;
        
        int left_smaller = bit.query(rank + 1);
        
        int left_greater = i - left_smaller;
        
        int right_greater = total_greater - left_greater;
        
        total_moves += min(left_greater, right_greater);
        
        bit.add(rank + 1, 1);
    }

    cout << total_moves << "\n";

    return 0;
}