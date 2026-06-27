#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

int64 countDigit(long long x, int d) {
    if (x <= 0) return (d == 0 ? 1 : 0);
    int64 res = 0;
    for (int64 pos = 1; pos <= x; pos *= 10) {
        int64 higher = x / (pos * 10);
        int64 cur = (x / pos) % 10;
        int64 lower = x % pos;

        if (d > 0) {
            if (cur > d) {
                res += (higher + 1) * pos;
            } else if (cur == d) {
                res += higher * pos + (lower + 1);
            } else {
                res += higher * pos;
            }
        } else {
            if (higher == 0) continue;

            if (cur > 0) {
                res += (higher) * pos;
            } else if (cur == 0) {
                res += (higher - 1) * pos + (lower + 1);
            }
        }
    }
    return res;
}

bool can(long long x, long long n) {
    if (x <= 0) return true;
    long long cnt[10];
    for (int d = 0; d <= 9; ++d) {
        long long c = countDigit(x, d);
        if (d == 0) c -= 1;
        cnt[d] = c;
        if (cnt[d] > n) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    if (!(cin >> n)) return 0;

    long long lo = 1, hi = 1000000000000000000LL;
    long long ans = 0;
    while (lo <= hi) {
        long long mid = lo + (hi - lo) / 2;
        if (can(mid, n)) {
            ans = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }

    cout << ans << '\n';
    return 0;
}