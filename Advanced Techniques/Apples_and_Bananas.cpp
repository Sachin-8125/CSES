#include <iostream>
#include <vector>
#include <complex>
#include <cmath>

using namespace std;

typedef complex<double> cd;
const double PI = acos(-1);

void fft(vector<cd>& a, bool invert) {
    int n = a.size();
    
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    
    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i + j], v = a[i + j + len/2] * w;
                a[i + j] = u + v;
                a[i + j + len/2] = u - v;
                w *= wlen;
            }
        }
    }
    
    if (invert) {
        for (cd& x : a) x /= n;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int k, n, m;
    cin >> k >> n >> m;
    
    vector<long long> A(k + 1, 0), B(k + 1, 0);
    
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        A[a]++;
    }
    
    for (int i = 0; i < m; i++) {
        int b;
        cin >> b;
        B[b]++;
    }
    
    vector<cd> fa(A.begin(), A.end()), fb(B.begin(), B.end());
    int sz = 1;
    while (sz < 2 * k + 1) sz <<= 1;
    fa.resize(sz);
    fb.resize(sz);
    
    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < sz; i++) fa[i] *= fb[i];
    fft(fa, true);
    
    for (int w = 2; w <= 2 * k; w++) {
        cout << (long long)round(fa[w].real());
        if (w < 2 * k) cout << " ";
    }
    cout << "\n";
    
    return 0;
}