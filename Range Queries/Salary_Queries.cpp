#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct FenwickTree {
    int n;
    vector<int> bit;

    FenwickTree(int n) : n(n), bit(n + 1, 0) {}

    void add(int idx, int val) {
        for (; idx <= n; idx += idx & -idx)
            bit[idx] += val;
    }

    int query(int idx) {
        int sum = 0;
        for (; idx > 0; idx -= idx & -idx)
            sum += bit[idx];
        return sum;
    }

    int query(int l, int r) {
        if (l > r) return 0;
        return query(r) - query(l - 1);
    }
};

struct Query {
    char type;
    int a, b;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    vector<int> p(n);
    vector<int> values;
    values.reserve(n + 2 * q);

    for (int i = 0; i < n; ++i) {
        cin >> p[i];
        values.push_back(p[i]);
    }

    vector<Query> queries(q);
    for (int i = 0; i < q; ++i) {
        cin >> queries[i].type >> queries[i].a >> queries[i].b;
        if (queries[i].type == '!') {
            values.push_back(queries[i].b);
        } else {
            values.push_back(queries[i].a);
            values.push_back(queries[i].b);
        }
    }

    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());

    auto get_compressed_idx = [&](int val) {
        return lower_bound(values.begin(), values.end(), val) - values.begin() + 1;
    };

    int num_elements = values.size();
    FenwickTree ft(num_elements);

    for (int i = 0; i < n; ++i) {
        ft.add(get_compressed_idx(p[i]), 1);
    }

    for (int i = 0; i < q; ++i) {
        if (queries[i].type == '!') {
            int employee_idx = queries[i].a - 1;
            int old_salary = p[employee_idx];
            int new_salary = queries[i].b;

            ft.add(get_compressed_idx(old_salary), -1);
            ft.add(get_compressed_idx(new_salary), 1);
            
            p[employee_idx] = new_salary;
        } else {
            int a = queries[i].a;
            int b = queries[i].b;

            int compressed_a = lower_bound(values.begin(), values.end(), a) - values.begin() + 1;
            int compressed_b = upper_bound(values.begin(), values.end(), b) - values.begin();

            cout << ft.query(compressed_a, compressed_b) << "\n";
        }
    }

    return 0;
}