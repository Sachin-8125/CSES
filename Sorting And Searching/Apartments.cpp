#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    long long k;
    if (!(cin >> n >> m >> k)) return 0;

    vector<long long> a(n), b(m);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int j = 0; j < m; ++j) cin >> b[j];

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    int i = 0, j = 0, ans = 0;
    while (i < n && j < m) {
        if (b[j] < a[i] - k) {
            // apartment too small for this applicant
            ++j;
        } else if (b[j] > a[i] + k) {
            // apartment too big for this applicant -> try next applicant
            ++i;
        } else {
            // match
            ++ans;
            ++i;
            ++j;
        }
    }

    cout << ans << '\n';
    return 0;
}
