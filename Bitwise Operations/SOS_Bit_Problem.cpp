#include <iostream>
#include <vector>

using namespace std;

const int MAX_BITS = 20;
const int MAX_VAL = 1 << MAX_BITS;

int dp_sub[MAX_VAL];
int dp_sup[MAX_VAL];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> x(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
        dp_sub[x[i]]++;
        dp_sup[x[i]]++;
    }

    for (int i = 0; i < MAX_BITS; i++) {
        for (int mask = 0; mask < MAX_VAL; mask++) {
            if (mask & (1 << i)) {
                dp_sub[mask] += dp_sub[mask ^ (1 << i)];
            } else {
                dp_sup[mask] += dp_sup[mask | (1 << i)];
            }
        }
    }

    int full_mask = MAX_VAL - 1;
    for (int i = 0; i < n; i++) {
        int ans1 = dp_sub[x[i]];
        int ans2 = dp_sup[x[i]];
        int ans3 = n - dp_sub[(~x[i]) & full_mask];
        cout << ans1 << " " << ans2 << " " << ans3 << "\n";
    }

    return 0;
}