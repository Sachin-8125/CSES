#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long k;
    cin >> n >> k;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    vector<long long> b(2 * n);
    for (int i = 0; i < 2 * n; ++i) b[i] = a[i % n];

    vector<long long> pref(2 * n + 1, 0);
    for (int i = 0; i < 2 * n; ++i) pref[i + 1] = pref[i] + b[i];

    vector<int> nxt(2 * n);
    int r = 0;
    for (int i = 0; i < 2 * n; ++i) {
        if (r < i) r = i;
        while (r < 2 * n && pref[r + 1] - pref[i] <= k) ++r;
        nxt[i] = r;
    }

    int LOG = 20;
    vector<vector<int>> up(LOG, vector<int>(2 * n));
    for (int i = 0; i < 2 * n; ++i) up[0][i] = nxt[i];

    for (int p = 1; p < LOG; ++p) {
        for (int i = 0; i < 2 * n; ++i) {
            int mid = up[p - 1][i];
            up[p][i] = (mid < 2 * n ? up[p - 1][mid] : 2 * n);
        }
    }

    int ans = n;

    for (int start = 0; start < n; ++start) {
        int pos = start;
        int need = start + n;
        int cnt = 0;

        for (int p = LOG - 1; p >= 0; --p) {
            int nxtPos = up[p][pos];
            if (nxtPos < need && nxtPos < 2 * n) {
                pos = nxtPos;
                cnt += (1 << p);
            }
        }
        cnt++;
        ans = min(ans, cnt);
    }

    cout << ans << '\n';
    return 0;
}