#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct cd {
    double r, i;
    cd(double r = 0, double i = 0) : r(r), i(i) {}
    cd operator+(const cd& o) const { return {r + o.r, i + o.i}; }
    cd operator-(const cd& o) const { return {r - o.r, i - o.i}; }
    cd operator*(const cd& o) const { return {r * o.r - i * o.i, r * o.i + i * o.r}; }
    cd& operator/=(double d) { r /= d; i /= d; return *this; }
};

const double PI = acos(-1.0);

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
            cd w(1, 0);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w = w * wlen;
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

    int n, m;
    cin >> n >> m;

    vector<long long> a(n), b(m);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < m; i++) cin >> b[i];

    reverse(b.begin(), b.end());

    int sz = 1;
    while (sz < n + m) sz <<= 1;

    vector<cd> fa(sz), fb(sz);
    for (int i = 0; i < n; i++) fa[i] = cd(a[i], 0);
    for (int i = 0; i < m; i++) fb[i] = cd(b[i], 0);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < sz; i++) fa[i] = fa[i] * fb[i];
    fft(fa, true);

    for (int i = 0; i < n + m - 1; i++) {
        cout << (long long)round(fa[i].r);
        if (i < n + m - 2) cout << " ";
    }
    cout << "\n";

    return 0;
}