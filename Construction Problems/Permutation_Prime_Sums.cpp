#include <iostream>
#include <vector>

using namespace std;

bool is_prime(int num) {
    if (num < 2) return false;
    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        a[i] = i + 1;
    }

    int current_n = n;
    while (current_n > 0) {
        int target_sum = current_n + 1;
        while (!is_prime(target_sum)) {
            target_sum++;
        }

        int left = target_sum - current_n;
        for (int i = current_n; i >= left; --i) {
            b[i - 1] = target_sum - i;
        }
        current_n = left - 1;
    }

    for (int i = 0; i < n; ++i) {
        cout << a[i] << (i == n - 1 ? "" : " ");
    }
    cout << "\n";

    for (int i = 0; i < n; ++i) {
        cout << b[i] << (i == n - 1 ? "" : " ");
    }
    cout << "\n";

    return 0;
}