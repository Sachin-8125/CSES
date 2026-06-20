#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<pair<int,int>> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first;
        a[i].second = i;   // store original index
    }

    stable_sort(a.begin(), a.end(), [](const pair<int,int>& x, const pair<int,int>& y) {
        return x.first < y.first;
    });

    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans = max(ans, a[i].second - i);
    }

    cout << ans << "\n";
    return 0;
}