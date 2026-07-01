#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<long long> a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];

    vector<long long> c(n);
    long long current_sum = 0;
    
    for (int i = 0; i < n; ++i) {
        current_sum += (a[i] - b[i]);
        c[i] = current_sum;
    }

    sort(c.begin(), c.end());
    long long median = c[n / 2];

    long long total_steps = 0;
    for (int i = 0; i < n; ++i) {
        total_steps += abs(c[i] - median);
    }

    cout << total_steps << "\n";

    return 0;
}