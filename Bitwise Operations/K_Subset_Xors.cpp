#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct LinearBasis {
    int basis[31];
    int sz;

    LinearBasis() {
        for (int i = 0; i <= 30; i++) basis[i] = 0;
        sz = 0;
    }

    void insert(int x) {
        for (int i = 30; i >= 0; i--) {
            if (!(x & (1 << i))) continue;
            if (!basis[i]) {
                basis[i] = x;
                sz++;
                return;
            }
            x ^= basis[i];
        }
    }

    vector<int> get_rref_basis() {
        for (int i = 30; i >= 0; i--) {
            if (!basis[i]) continue;
            for (int j = i + 1; j <= 30; j++) {
                if (basis[j] & (1 << i)) {
                    basis[j] ^= basis[i];
                }
            }
        }
        vector<int> g;
        for (int i = 0; i <= 30; i++) {
            if (basis[i]) g.push_back(basis[i]);
        }
        return g;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long k;
    if (!(cin >> n >> k)) return 0;

    LinearBasis lb;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        lb.insert(x);
    }

    vector<int> g = lb.get_rref_basis();
    int d = lb.sz;

    // Each distinct XOR sum appears 2^(n-d) times.
    // Since k is at most 2*10^5, we can handle this.
    long long copies = 1;
    for (int i = 0; i < n - d; i++) {
        copies *= 2;
        if (copies >= k) {
            copies = k;
            break;
        }
    }

    long long printed = 0;
    for (int m = 0; printed < k; m++) {
        int val = 0;
        for (int i = 0; i < d; i++) {
            if ((m >> i) & 1) {
                val ^= g[i];
            }
        }
        
        for (int j = 0; j < copies && printed < k; j++) {
            cout << val << (printed + 1 == k ? "" : " ");
            printed++;
        }
    }
    cout << endl;

    return 0;
}