#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Query {
    int l, r, id;
};

int block_size;

bool compareQueries(const Query& a, const Query& b) {
    int block_a = a.l / block_size;
    int block_b = b.l / block_size;
    if (block_a != block_b) {
        return block_a < block_b;
    }
    return (block_a % 2 == 1) ? (a.r < b.r) : (a.r > b.r);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    vector<int> x(n);
    vector<int> values(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
        values[i] = x[i];
    }

    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());
    for (int i = 0; i < n; i++) {
        x[i] = lower_bound(values.begin(), values.end(), x[i]) - values.begin();
    }

    block_size = max(1, (int)(n / sqrt(q)));

    vector<Query> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].l--;
        queries[i].r--;
        queries[i].id = i;
    }

    sort(queries.begin(), queries.end(), compareQueries);

    vector<int> freq(values.size(), 0);
    vector<int> ans(q);
    int current_distinct = 0;
    int curr_l = 0, curr_r = -1;

    auto add = [&](int index) {
        if (freq[x[index]] == 0) {
            current_distinct++;
        }
        freq[x[index]]++;
    };

    auto remove = [&](int index) {
        freq[x[index]]--;
        if (freq[x[index]] == 0) {
            current_distinct--;
        }
    };

    for (const auto& query : queries) {
        while (curr_l > query.l) {
            curr_l--;
            add(curr_l);
        }
        while (curr_r < query.r) {
            curr_r++;
            add(curr_r);
        }
        while (curr_l < query.l) {
            remove(curr_l);
            curr_l++;
        }
        while (curr_r > query.r) {
            remove(curr_r);
            curr_r--;
        }
        ans[query.id] = current_distinct;
    }

    for (int i = 0; i < q; i++) {
        cout << ans[i] << "\n";
    }

    return 0;
}