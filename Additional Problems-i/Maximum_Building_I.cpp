#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> h(m, 0);
    long long ans = 0;

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++) {
            if (s[j] == '.') h[j]++;
            else h[j] = 0;
        }

        stack<int> st;
        for (int j = 0; j <= m; j++) {
            int cur = (j == m ? 0 : h[j]);
            while (!st.empty() && h[st.top()] > cur) {
                int height = h[st.top()];
                st.pop();
                int left = st.empty() ? -1 : st.top();
                ans = max(ans, 1LL * height * (j - left - 1));
            }
            st.push(j);
        }
    }

    cout << ans << '\n';
    return 0;
}