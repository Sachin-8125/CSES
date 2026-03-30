#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Range {
    int l, r, id;
    
    bool operator<(const Range& other) const {
        if (l == other.l) return r > other.r;
        return l < other.l;
    }
};

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

    vector<Range> ranges(n);
    vector<int> r_vals(n);
    
    for (int i = 0; i < n; ++i) {
        cin >> ranges[i].l >> ranges[i].r;
        ranges[i].id = i;
        r_vals[i] = ranges[i].r;
    }

    sort(r_vals.begin(), r_vals.end());
    r_vals.erase(unique(r_vals.begin(), r_vals.end()), r_vals.end());

    auto get_compressed = [&](int r) {
        return lower_bound(r_vals.begin(), r_vals.end(), r) - r_vals.begin() + 1;
    };

    sort(ranges.begin(), ranges.end());

    vector<int> contains(n, 0);
    vector<int> contained(n, 0);

    FenwickTree bit_contains(r_vals.size());
    for (int i = n - 1; i >= 0; --i) {
        int comp_r = get_compressed(ranges[i].r);
        contains[ranges[i].id] = bit_contains.query(comp_r);
        bit_contains.add(comp_r, 1);
    }

    FenwickTree bit_contained(r_vals.size());
    for (int i = 0; i < n; ++i) {
        int comp_r = get_compressed(ranges[i].r);
        contained[ranges[i].id] = bit_contained.query(r_vals.size()) - bit_contained.query(comp_r - 1);
        bit_contained.add(comp_r, 1);
    }

    for (int i = 0; i < n; ++i) {
        cout << contains[i] << (i == n - 1 ? "" : " ");
    }
    cout << "\n";
    
    for (int i = 0; i < n; ++i) {
        cout << contained[i] << (i == n - 1 ? "" : " ");
    }
    cout << "\n";

    return 0;
}