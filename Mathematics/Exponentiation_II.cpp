#include <iostream>
using namespace std;
typedef long long ll;

ll power(ll base, ll exp, ll mod) {
    ll res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    while (n--) {
        ll a, b, c;
        cin >> a >> b >> c;
        
        ll MOD1 = 1000000007;
        ll MOD2 = 1000000006; // MOD1 - 1
        
        ll exponent = power(b, c, MOD2);
        cout << power(a, exponent, MOD1) << "\n";
    }
    return 0;
}