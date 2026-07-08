#include <iostream>
#include <vector>
#include <string>
#include <complex>
#include <cmath>

using namespace std;

using cd = complex<double>;
const double PI = acos(-1);

void fft(vector<cd>& a, bool invert) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;
        if (i < j)
            swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i + j];
                cd v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert) {
        for (cd& x : a)
            x /= n;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    if (!(cin >> s)) return 0;
    
    int n = s.length();
    vector<long long> C(n + 1, 0);
    C[0] = 1;
    
    int pref = 0;
    long long zero_count = 0;
    long long current_zeros = 0;

    for (int i = 0; i < n; ++i) {
        if (s[i] == '1') {
            pref++;
            current_zeros = 0;
        } else {
            current_zeros++;
            zero_count += current_zeros;
        }
        C[pref]++;
    }

    int sz = 1;
    while (sz < 2 * n + 1) sz <<= 1;
    
    vector<cd> a(sz), b(sz);
    for (int i = 0; i <= n; i++) {
        a[i] = C[i];
        b[i] = C[n - i];
    }

    fft(a, false);
    fft(b, false);
    for (int i = 0; i < sz; i++) {
        a[i] *= b[i];
    }
    fft(a, true);

    vector<long long> ans(n + 1);
    ans[0] = zero_count; 
    
    for (int k = 1; k <= n; k++) {
        ans[k] = llround(a[n + k].real());
    }

    for (int i = 0; i <= n; i++) {
        cout << ans[i] << (i == n ? "" : " ");
    }
    cout << "\n";

    return 0;
}