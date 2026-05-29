#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct FT {
    int n;
    vector<int> t;

    FT(int m) {
        n = m;
        t.assign(m + 1, 0);
    }

    void add(int v, vector<int>& uv, int d) {
        int idx = lower_bound(uv.begin(), uv.end(), v) - uv.begin() + 1;
        for (; idx <= n; idx += idx & -idx) t[idx] += d;
    }

    int qry(int idx) {
        int s = 0;
        for (; idx > 0; idx -= idx & -idx) s += t[idx];
        return s;
    }

    int cg(int v, vector<int>& uv, int total) {
        int idx = lower_bound(uv.begin(), uv.end(), v) - uv.begin() + 1;
        return total - qry(idx);
    }

    int cs(int v, vector<int>& uv) {
        int idx = lower_bound(uv.begin(), uv.end(), v) - uv.begin();
        return qry(idx);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<int> a(n);
    vector<int> uv(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        uv[i] = a[i];
    }

    sort(uv.begin(), uv.end());
    uv.erase(unique(uv.begin(), uv.end()), uv.end());

    int m = uv.size();
    FT bit(m);

    long long inv = 0;

    for (int i = 0; i < k; i++) {
        inv += bit.cg(a[i], uv, i);
        bit.add(a[i], uv, 1);
    }

    cout << inv;

    for (int i = k; i < n; i++) {
        int l = a[i - k];
        bit.add(l, uv, -1);
        inv -= bit.cs(l, uv);

        int r = a[i];
        inv += bit.cg(r, uv, k - 1);
        bit.add(r, uv, 1);

        cout << " " << inv;
    }
    cout << "\n";

    return 0;
}
