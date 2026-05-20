#include <iostream>
#include <vector>

using namespace std;

const int MAXX = 1000001;
int cnt[MAXX];
int mu[MAXX];
int primes[MAXX], pcnt = 0;
bool is_prime[MAXX];

void sieve() {
    fill(is_prime + 2, is_prime + MAXX, true);
    mu[1] = 1;
    for (int i = 2; i < MAXX; i++) {
        if (is_prime[i]) {
            primes[pcnt++] = i;
            mu[i] = -1;
        }
        for (int j = 0; j < pcnt && i * primes[j] < MAXX; j++) {
            is_prime[i * primes[j]] = false;
            if (i % primes[j] == 0) {
                mu[i * primes[j]] = 0;
                break;
            }
            mu[i * primes[j]] = -mu[i];
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    sieve();

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }

    long long total_coprime = 0;
    for (int d = 1; d < MAXX; d++) {
        if (mu[d] == 0) continue;
        
        long long multiples = 0;
        for (int m = d; m < MAXX; m += d) {
            multiples += cnt[m];
        }
        
        long long pairs = (multiples * (multiples - 1)) / 2;
        if (mu[d] == 1) {
            total_coprime += pairs;
        } else {
            total_coprime -= pairs;
        }
    }

    cout << total_coprime << endl;

    return 0;
}