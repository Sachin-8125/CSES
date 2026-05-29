#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    long long x, a, b, c;
    cin >> x >> a >> b >> c;

    vector<int> arr(n);
    arr[0] = x;
    for (int i = 1; i < n; i++) {
        arr[i] = (a * arr[i - 1] + b) % c;
    }

    vector<int> pre(n), suf(n);
    for (int i = 0; i < n; i++) {
        if (i % k == 0) pre[i] = arr[i];
        else pre[i] = pre[i - 1] | arr[i];
    }

    for (int i = n - 1; i >= 0; i--) {
        if (i == n - 1 || (i + 1) % k == 0) suf[i] = arr[i];
        else suf[i] = suf[i + 1] | arr[i];
    }

    int ans = 0;
    for (int i = 0; i <= n - k; i++) {
        ans ^= (suf[i] | pre[i + k - 1]);
    }

    cout << ans << endl;

    return 0;
}