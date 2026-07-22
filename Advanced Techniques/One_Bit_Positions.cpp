#include <iostream>
#include <vector>
#include <complex>
#include <string>
#include <cmath>

using namespace std;

using cd = complex<double>;
const double PI = acos(-1);

void fft(vector<cd>& a, bool invert) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) {
            j ^= bit;
        }
        j ^= bit;
        if (i < j) {
            swap(a[i], a[j]);
        }
    }
    
    for (int len = 2; len <= n; len <<= 1) {
        double angle = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(angle), sin(angle));
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
        for (cd& x : a) {
            x /= n;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    if (!(cin >> s)) return 0;
    
    int n = s.length();
    
    int sz = 1;
    while (sz < 2 * n) sz <<= 1;
    
    vector<cd> fa(sz), fb(sz);
    for (int i = 0; i < n; i++) {
        fa[i] = s[i] - '0';
        fb[i] = s[n - 1 - i] - '0';
    }
    
    fft(fa, false);
    fft(fb, false);
    
    for (int i = 0; i < sz; i++) {
        fa[i] *= fb[i];
    }
    
    fft(fa, true);
    
    for (int k = 1; k < n; k++) {
        long long res = round(fa[n - 1 - k].real());
        cout << res << (k == n - 1 ? "" : " ");
    }
    cout << "\n";
    
    return 0;
}