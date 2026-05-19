#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

class FenwickTree {
private:
    vector<int> tree;
    int n;

public:
    FenwickTree(int size) : n(size), tree(size + 1, 0) {}

    void update(int idx, int val) {
        while (idx <= n) {
            tree[idx] = (tree[idx] + val) % MOD;
            idx += idx & -idx;
        }
    }

    int query(int idx) {
        int sum = 0;
        while (idx > 0) {
            sum = (sum + tree[idx]) % MOD;
            idx -= idx & -idx;
        }
        return sum;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    vector<int> sorted_arr = arr;
    sort(sorted_arr.begin(), sorted_arr.end());
    sorted_arr.erase(unique(sorted_arr.begin(), sorted_arr.end()), sorted_arr.end());

    auto getCompressed = [&](int val) {
        return lower_bound(sorted_arr.begin(), sorted_arr.end(), val) - sorted_arr.begin() + 1;
    };

    int num_unique = sorted_arr.size();
    FenwickTree ft(num_unique);

    long long total = 0;

    for (int i = 0; i < n; i++) {
        int compressed_val = getCompressed(arr[i]);
        
        int sum_before = (compressed_val > 1) ? ft.query(compressed_val - 1) : 0;
        
        int dp_i = (1 + sum_before) % MOD;
        
        ft.update(compressed_val, dp_i);
        
        total = (total + dp_i) % MOD;
    }

    cout << total << endl;

    return 0;
}