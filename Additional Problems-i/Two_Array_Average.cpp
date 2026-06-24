#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    vector<double> a(n), b(n);
    double lo = 1e18, hi = 0.0;
    for (int i = 0; i < n; ++i) {
        long long x;
        cin >> x;
        a[i] = (double)x;
        lo = min(lo, a[i]);
        hi = max(hi, a[i]);
    }
    for (int i = 0; i < n; ++i) {
        long long x;
        cin >> x;
        b[i] = (double)x;
        lo = min(lo, b[i]);
        hi = max(hi, b[i]);
    }

    double L = lo, R = hi;
    auto can = [&](double x) {
        double bestA = -1e300, cur = 0.0;
        for (int i = 0; i < n; ++i) {
            cur += a[i] - x;
            if (cur > bestA) bestA = cur;
        }
        double bestB = -1e300;
        cur = 0.0;
        for (int i = 0; i < n; ++i) {
            cur += b[i] - x;
            if (cur > bestB) bestB = cur;
        }
        return bestA + bestB >= 0.0;
    };

    for (int it = 0; it < 60; ++it) {
        double mid = (L + R) * 0.5;
        if (can(mid)) L = mid;
        else R = mid;
    }
    double bestAvg = L;

    double curA = 0.0, bestA = -1e300;
    int bestI = 1;
    for (int i = 0; i < n; ++i) {
        curA += a[i] - bestAvg;
        if (curA > bestA) {
            bestA = curA;
            bestI = i + 1;
        }
    }
    double curB = 0.0, bestB = -1e300;
    int bestJ = 1;
    for (int j = 0; j < n; ++j) {
        curB += b[j] - bestAvg;
        if (curB > bestB) {
            bestB = curB;
            bestJ = j + 1;
        }
    }

    cout << bestI << ' ' << bestJ << '\n';
    return 0;
}