#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n;
    int k;
    cin >> n >> k;

    vector<ll> a(k);
    for (int i = 0; i < k; i++) {
        cin >> a[i];
    }

    ll res = 0;

    for (int i = 1; i < (1 << k); i++) {
        ll product = 1;
        int set_bits = 0;
        bool overflow = false;

        for (int j = 0; j < k; j++) {
            if ((i >> j) & 1) {
                set_bits++;
                // Check if product * a[j] > n to avoid overflow
                if (product > n / a[j]) {
                    overflow = true;
                    break;
                }
                product *= a[j];
            }
        }

        if (!overflow) {
            if (set_bits % 2 == 1) {
                res += n / product;
            } else {
                res -= n / product;
            }
        }
    }

    cout << res << endl;

    return 0;
}