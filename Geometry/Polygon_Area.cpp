#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<long long> x(n), y(n);

    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
    }

    long long res = 0;

    for (int i = 0; i < n; ++i) {
        int next_i = (i + 1) % n; 
        res += (x[i] * y[next_i]) - (x[next_i] * y[i]);
    }

    res = abs(res);

    cout << res << "\n";

    return 0;
}