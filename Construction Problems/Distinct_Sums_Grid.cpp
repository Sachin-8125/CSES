#include <iostream>
#include <vector>
#include <numeric>
#include <random>
#include <algorithm>
#include <chrono>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    if (n <= 3) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    vector<vector<int>> grid(n, vector<int>(n));
    vector<int> vals;
    vals.reserve(n * n);
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < n; ++j) {
            vals.push_back(i);
        }
    }

    auto start_time = chrono::steady_clock::now();
    mt19937 rng(1337);
    shuffle(vals.begin(), vals.end(), rng);

    vector<int> row_sum(n, 0), col_sum(n, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            grid[i][j] = vals[i * n + j];
            row_sum[i] += grid[i][j];
            col_sum[j] += grid[i][j];
        }
    }

    vector<int> freq(n * n + 1, 0);
    int distinct = 0;

    auto add = [&](int sum) {
        if (freq[sum] == 0) distinct++;
        freq[sum]++;
    };
    auto remove = [&](int sum) {
        freq[sum]--;
        if (freq[sum] == 0) distinct--;
    };

    for (int i = 0; i < n; ++i) {
        add(row_sum[i]);
        add(col_sum[i]);
    }

    int current_distinct = distinct;
    int iterations = 0;
    vector<int> coll_r(n), coll_c(n);

    while (current_distinct < 2 * n) {
        iterations++;
        if ((iterations & 1023) == 0) {
            auto current_time = chrono::steady_clock::now();
            double elapsed = chrono::duration<double>(current_time - start_time).count();
            if (elapsed > 0.95) {
                break;
            }
        }

        if (iterations % 200000 == 0) {
            shuffle(vals.begin(), vals.end(), rng);
            fill(row_sum.begin(), row_sum.end(), 0);
            fill(col_sum.begin(), col_sum.end(), 0);
            fill(freq.begin(), freq.end(), 0);
            distinct = 0;

            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    grid[i][j] = vals[i * n + j];
                    row_sum[i] += grid[i][j];
                    col_sum[j] += grid[i][j];
                }
            }
            for (int i = 0; i < n; ++i) {
                add(row_sum[i]);
                add(col_sum[i]);
            }
            current_distinct = distinct;
            continue;
        }

        int cr_cnt = 0, cc_cnt = 0;
        if (current_distinct < 2 * n && rng() % 4 != 0) {
            for (int i = 0; i < n; ++i) {
                if (freq[row_sum[i]] > 1) coll_r[cr_cnt++] = i;
                if (freq[col_sum[i]] > 1) coll_c[cc_cnt++] = i;
            }
        }

        int r1, c1, r2, c2;
        if (cr_cnt > 0 && (cc_cnt == 0 || rng() % 2 == 0)) {
            r1 = coll_r[rng() % cr_cnt];
            c1 = rng() % n;
        } else if (cc_cnt > 0) {
            r1 = rng() % n;
            c1 = coll_c[rng() % cc_cnt];
        } else {
            r1 = rng() % n;
            c1 = rng() % n;
        }

        r2 = rng() % n;
        c2 = rng() % n;

        int v1 = grid[r1][c1];
        int v2 = grid[r2][c2];
        if (v1 == v2) continue;

        int r_idx[2], c_idx[2];
        int r_cnt = 0, c_cnt = 0;
        
        r_idx[r_cnt++] = r1;
        if (r2 != r1) r_idx[r_cnt++] = r2;
        
        c_idx[c_cnt++] = c1;
        if (c2 != c1) c_idx[c_cnt++] = c2;

        for (int i = 0; i < r_cnt; ++i) remove(row_sum[r_idx[i]]);
        for (int i = 0; i < c_cnt; ++i) remove(col_sum[c_idx[i]]);

        row_sum[r1] += v2 - v1;
        col_sum[c1] += v2 - v1;
        row_sum[r2] += v1 - v2;
        col_sum[c2] += v1 - v2;

        for (int i = 0; i < r_cnt; ++i) add(row_sum[r_idx[i]]);
        for (int i = 0; i < c_cnt; ++i) add(col_sum[c_idx[i]]);

        bool accept = false;
        if (distinct > current_distinct) {
            accept = true;
        } else if (distinct == current_distinct) {
            if (rng() % 100 < 90) accept = true;
        } else {
            if (rng() % 1000 < 5) accept = true;
        }

        if (accept) {
            swap(grid[r1][c1], grid[r2][c2]);
            current_distinct = distinct;
        } else {
            for (int i = 0; i < r_cnt; ++i) remove(row_sum[r_idx[i]]);
            for (int i = 0; i < c_cnt; ++i) remove(col_sum[c_idx[i]]);

            row_sum[r1] -= v2 - v1;
            col_sum[c1] -= v2 - v1;
            row_sum[r2] -= v1 - v2;
            col_sum[c2] -= v1 - v2;

            for (int i = 0; i < r_cnt; ++i) add(row_sum[r_idx[i]]);
            for (int i = 0; i < c_cnt; ++i) add(col_sum[c_idx[i]]);
        }
    }

    if (current_distinct < 2 * n) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << grid[i][j] << (j == n - 1 ? "" : " ");
        }
        cout << "\n";
    }

    return 0;
}