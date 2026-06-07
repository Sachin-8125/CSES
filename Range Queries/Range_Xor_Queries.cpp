#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    vector<int> pref(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
        int val;
        cin >> val;
        pref[i] = pref[i - 1] ^ val;
    }

    for (int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        int ans = pref[b] ^ pref[a - 1];
        cout << ans << "\n";
    }

    return 0;
}
