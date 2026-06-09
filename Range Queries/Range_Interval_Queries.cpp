#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct FenwickTree {
    int size;
    vector<int> tree;

    FenwickTree(int n) {
        size = n;
        tree.assign(n + 1, 0);
    }

    void update(int i, int delta) {
        for (; i <= size; i += i & -i) {
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

    int query(int l, int r) {
        if (l > r) return 0;
        return query(r) - query(l - 1);
    }
};

struct SubQuery {
    int c, d;
    int query_id;
    int type;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    vector<int> x(n + 1);
    vector<int> values;
    values.reserve(n + 2 * q);

    for (int i = 1; i <= n; i++) {
        cin >> x[i];
        values.push_back(x[i]);
    }

    struct QueryRange {
        int a, b, c, d;
    };
    vector<QueryRange> queries(q);
    
    vector<vector<SubQuery>> bucket(n + 1);

    for (int i = 0; i < q; i++) {
        cin >> queries[i].a >> queries[i].b >> queries[i].c >> queries[i].d;
        values.push_back(queries[i].c);
        values.push_back(queries[i].d);

        bucket[queries[i].b].push_back({queries[i].c, queries[i].d, i, 1});
        bucket[queries[i].a - 1].push_back({queries[i].c, queries[i].d, i, -1});
    }

    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());

    auto get_compressed = [&](int val) {
        return lower_bound(values.begin(), values.end(), val) - values.begin() + 1;
    };

    int compressed_max_val = values.size();
    FenwickTree bit(compressed_max_val);
    vector<int> ans(q, 0);

    for (const auto& sub_q : bucket[0]) {
    }

    for (int i = 1; i <= n; i++) {
        int comp_val = get_compressed(x[i]);
        bit.update(comp_val, 1);

        for (const auto& sub_q : bucket[i]) {
            int comp_c = get_compressed(sub_q.c);
            int comp_d = get_compressed(sub_q.d);
            int count = bit.query(comp_c, comp_d);
            ans[sub_q.query_id] += sub_q.type * count;
        }
    }

    for (int i = 0; i < q; i++) {
        cout << ans[i] << "\n";
    }

    return 0;
}