#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 200005;
const int MOD = 1e9 + 7;

int spf[MAXN];
int max_exp[MAXN];

void sieve() {
    for (int i = 2; i < MAXN; i++) {
        if (spf[i] == 0) {
            for (int j = i; j < MAXN; j += i) {
                if (spf[j] == 0) spf[j] = i;
            }
        }
    }
}

long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    sieve();

    int n;
    cin >> n;

    vector<int> p(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }

    vector<bool> visited(n + 1, false);
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            int curr = i;
            int length = 0;
            while (!visited[curr]) {
                visited[curr] = true;
                curr = p[curr];
                length++;
            }

            int temp = length;
            while (temp > 1) {
                int factor = spf[temp];
                int count = 0;
                while (temp % factor == 0) {
                    temp /= factor;
                    count++;
                }
                max_exp[factor] = max(max_exp[factor], count);
            }
        }
    }

    long long result = 1;
    for (int i = 2; i <= n; i++) {
        if (max_exp[i] > 0) {
            result = (result * power(i, max_exp[i])) % MOD;
        }
    }

    cout << result << endl;

    return 0;
}
