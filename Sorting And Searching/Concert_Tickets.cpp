#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    multiset<long long> tickets;
    for (int i = 0; i < n; ++i) {
        long long h;
        cin >> h;
        tickets.insert(h);
    }

    for (int i = 0; i < m; ++i) {
        long long t;
        cin >> t;
        auto it = tickets.upper_bound(t);
        if (it == tickets.begin()) {
            cout << -1 << "\n";
        } else {
            --it; // largest price <= t
            cout << *it << "\n";
            tickets.erase(it);
        }
    }
    return 0;
}
