#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        long long val;
        cin >> val;
        if ((i & (n - 1)) == i) {
            ans ^= val;
        }
    }

    cout << ans << "\n";

    return 0;
}
