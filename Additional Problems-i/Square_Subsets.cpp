#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

const int MAX_VAL = 5001;
const int MOD = 1e9 + 7;

vector<int> primes;
int prime_idx[MAX_VAL];

void sieve() {
    vector<bool> is_prime(MAX_VAL, true);
    is_prime[0] = is_prime[1] = false;
    for (int p = 2; p < MAX_VAL; p++) {
        if (is_prime[p]) {
            prime_idx[p] = primes.size();
            primes.push_back(p);
            for (int i = 2 * p; i < MAX_VAL; i += p)
                is_prime[i] = false;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    sieve();
    int num_primes = primes.size();
    vector<bitset<670>> basis(num_primes);
    int basis_size = 0;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        bitset<670> mask;
        for (int j = 0; j < num_primes; j++) {
            int p = primes[j];
            if (p * p > x) break;
            int count = 0;
            while (x % p == 0) {
                count++;
                x /= p;
            }
            if (count % 2 == 1) {
                mask.set(j);
            }
        }
        if (x > 1) {
            mask.set(prime_idx[x]);
        }

        for (int j = 0; j < num_primes; j++) {
            if (!mask.test(j)) continue;
            if (basis[j].none()) {
                basis[j] = mask;
                basis_size++;
                break;
            }
            mask ^= basis[j];
        }
    }

    long long ans = 1;
    for (int i = 0; i < n - basis_size; i++) {
        ans = (ans * 2) % MOD;
    }
    cout << ans << endl;

    return 0;
}