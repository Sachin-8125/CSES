#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int d = n - k;
    int current_size = n;

    for (int bit = 0; bit <= 18; bit++) {
        if ((d >> bit) & 1) {
            int step = 1 << bit;
            for (int i = 0; i < current_size - step; i++) {
                a[i] ^= a[i + step];
            }
            current_size -= step;
        }
    }

    for (int i = 0; i < k; i++) {
        cout << a[i] << (i == k - 1 ? "" : " ");
    }
    cout << "\n";

    return 0;
}