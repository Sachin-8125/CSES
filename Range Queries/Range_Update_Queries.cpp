#include <iostream>
#include <vector>

using namespace std;

int n, q;
vector<long long> bit;

void update(int idx, long long val) {
    for (; idx <= n; idx += idx & -idx) {
        bit[idx] += val;
    }
}

long long query(int idx) {
    long long sum = 0;
    for (; idx > 0; idx -= idx & -idx) {
        sum += bit[idx];
    }
    return sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> q)) return 0;

    vector<long long> a(n + 1, 0);
    bit.assign(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        update(i, a[i] - a[i - 1]);
    }

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int a_idx, b_idx;
            long long u;
            cin >> a_idx >> b_idx >> u;
            update(a_idx, u);
            update(b_idx + 1, -u);
        } else {
            int k;
            cin >> k;
            cout << query(k) << "\n";
        }
    }

    return 0;
}