#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    vector<int> ans(n + 1, 0);
    stack<pair<long long,int>> st;

    for (int i = 1; i <= n; ++i) {
        while (!st.empty() && st.top().first >= a[i]) st.pop();
        ans[i] = st.empty() ? 0 : st.top().second;
        st.push({a[i], i});
    }
    for (int i = 1; i <= n; ++i) {
        if (i > 1) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}
