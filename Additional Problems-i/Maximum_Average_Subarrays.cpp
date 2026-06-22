#include <bits/stdc++.h>
using namespace std;
using ll = long long;

long double cross(const pair<ll,ll> &a, const pair<ll,ll> &b, const pair<ll,ll> &c) {
    long double x1 = b.first - a.first;
    long double y1 = b.second - a.second;
    long double x2 = c.first - a.first;
    long double y2 = c.second - a.second;
    return x1 * y2 - x2 * y1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    vector<ll> x(n + 1), pref(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> x[i];
        pref[i] = pref[i - 1] + x[i];
    }

    vector<pair<ll,ll>> hull;  

    auto slope = [&](const pair<ll,ll> &a, const pair<ll,ll> &b) -> long double {
        return (long double)(b.second - a.second) / (long double)(b.first - a.first);
    };

    vector<int> ans(n + 1);

    hull.push_back({0, pref[0]});

    for (int i = 1; i <= n; ++i) {
        pair<ll,ll> cur = {i, pref[i]};

        int low = 0, high = (int)hull.size() - 1;
        while (high - low >= 3) {
            int m1 = low + (high - low) / 3;
            int m2 = high - (high - low) / 3;
            long double s1 = slope(hull[m1], cur);
            long double s2 = slope(hull[m2], cur);
            if (s1 <= s2) {
                low = m1;
            } else {
                high = m2;
            }
        }
        int best = low;
        long double bestSlope = slope(hull[low], cur);
        for (int k = low + 1; k <= high; ++k) {
            long double s = slope(hull[k], cur);
            if (s > bestSlope + 1e-18L ||
                (fabsl(s - bestSlope) <= 1e-18L && hull[k].first < hull[best].first)) {
                bestSlope = s;
                best = k;
            }
        }

        ll j = hull[best].first;
        ans[i] = (int)(i - j);

        while (hull.size() >= 2 &&
               cross(hull[hull.size() - 2], hull.back(), cur) <= 0.0L) {
            hull.pop_back();
        }
        hull.push_back(cur);
    }

    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << (i == n ? '\n' : ' ');
    }

    return 0;
}