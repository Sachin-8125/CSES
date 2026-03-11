#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    long long x, a, b, c;
    cin >> x >> a >> b >> c;

    auto nextVal = [&](long long v) {
        return (a * v + b) % c;
    };

    // Build first window
    long long window_xor = 0;
    long long l = x, r = x;

    window_xor ^= r;
    for (int i = 1; i < k; i++) {
        r = nextVal(r);
        window_xor ^= r;
    }

    long long ans = window_xor;

    // Slide window
    for (int i = k; i < n; i++) {
        window_xor ^= l;          // remove leftmost (XOR removes in place)
        l = nextVal(l);
        r = nextVal(r);
        window_xor ^= r;          // add new right element
        ans ^= window_xor;
    }

    cout << ans << "\n";
    return 0;
}