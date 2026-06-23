#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    int m = n * (n - 1) / 2;

    vector<ll> b(m);
    for (ll &x : b) cin >> x;
    sort(b.begin(), b.end());

    auto build = [&](ll a0) -> vector<ll> {
        if (a0 <= 0) return {};

        multiset<ll> ms(b.begin(), b.end());
        vector<ll> a;
        a.reserve(n);
        a.push_back(a0);

        while ((int)a.size() < n) {
            if (ms.empty()) return {};
            ll nxt = *ms.begin() - a[0];
            if (nxt <= 0) return {};

            for (ll x : a) {
                auto it = ms.find(x + nxt);
                if (it == ms.end()) return {};
                ms.erase(it);
            }
            a.push_back(nxt);
        }

        if (!ms.empty()) return {};
        return a;
    };

    for (int k = 2; k < m; ++k) {
        ll num = b[0] + b[1] - b[k];
        if (num & 1) continue;

        ll a0 = num / 2;
        vector<ll> ans = build(a0);
        if ((int)ans.size() == n) {
            for (int i = 0; i < n; ++i) {
                cout << ans[i] << (i + 1 == n ? '\n' : ' ');
            }
            return 0;
        }
    }

    return 0;
}