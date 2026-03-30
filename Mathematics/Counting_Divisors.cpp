#include <iostream>
#include <vector>

using namespace std;

const int MAX = 1000001;
int spf[MAX];

void sieve() {
    for (int i = 2; i < MAX; i++) spf[i] = i;
    for (int i = 2; i * i < MAX; i++) {
        if (spf[i] == i) {
            for (int j = i * i; j < MAX; j += i)
                if (spf[j] == j) spf[j] = i;
        }
    }
}

int countDivisors(int x) {
    int totalDivisors = 1;
    while (x > 1) {
        int p = spf[x];
        int count = 0;
        while (x % p == 0) {
            count++;
            x /= p;
        }
        totalDivisors *= (count + 1);
    }
    return totalDivisors;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    sieve();

    int n;
    cin >> n;
    while (n--) {
        int x;
        cin >> x;
        if (x == 1) {
            cout << "1\n";
            continue;
        }
        cout << countDivisors(x) << "\n";
    }

    return 0;
}