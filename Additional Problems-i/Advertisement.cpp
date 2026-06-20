#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<long long> h(n);
    for (int i = 0; i < n; i++) cin >> h[i];

    stack<int> st;
    long long ans = 0;

    for (int i = 0; i <= n; i++) {
        long long cur = (i == n) ? 0 : h[i];

        while (!st.empty() && h[st.top()] >= cur) {
            long long height = h[st.top()]; st.pop();

            long long left = st.empty() ? 0 : st.top() + 1;
            long long width = i - left;

            ans = max(ans, height * width);
        }

        st.push(i);
    }

    cout << ans << "\n";
    return 0;
}