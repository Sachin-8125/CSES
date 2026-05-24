#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MOD = 1e9 + 7;
const int BASE = 313;

int n, m;
string s;
vector<long long> p;
vector<long long> bit1, bit2;

void add(vector<long long>& bit, int idx, long long val) {
    for (; idx <= n; idx += idx & -idx) {
        bit[idx] = (bit[idx] + val) % MOD;
    }
}

long long query(const vector<long long>& bit, int idx) {
    long long sum = 0;
    for (; idx > 0; idx -= idx & -idx) {
        sum = (sum + bit[idx]) % MOD;
    }
    return sum;
}

long long query_range(const vector<long long>& bit, int l, int r) {
    return (query(bit, r) - query(bit, l - 1) + MOD) % MOD;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> m)) return 0;
    cin >> s;
    s = " " + s; 

    p.resize(n + 2);
    p[0] = 1;
    for (int i = 1; i <= n + 1; ++i) {
        p[i] = (p[i - 1] * BASE) % MOD;
    }

    bit1.assign(n + 1, 0);
    bit2.assign(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
        long long val = s[i] - 'a' + 1;
        add(bit1, i, (val * p[i]) % MOD);
        add(bit2, i, (val * p[n - i + 1]) % MOD);
    }

    while (m--) {
        int type;
        cin >> type;
        if (type == 1) {
            int k;
            char c;
            cin >> k >> c;
            long long old_val = s[k] - 'a' + 1;
            long long new_val = c - 'a' + 1;
            long long diff = (new_val - old_val + MOD) % MOD;
            
            add(bit1, k, (diff * p[k]) % MOD);
            add(bit2, k, (diff * p[n - k + 1]) % MOD);
            s[k] = c;
        } else {
            int a, b;
            cin >> a >> b;
            long long h1 = query_range(bit1, a, b);
            long long h2 = query_range(bit2, a, b);

            h1 = (h1 * p[n - b]) % MOD;
            h2 = (h2 * p[a - 1]) % MOD;

            if (h1 == h2) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }

    return 0;
}