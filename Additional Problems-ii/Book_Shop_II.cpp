#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    if (!(cin >> n >> x)) return 0;

    vector<int> h(n);
    for (int i = 0; i < n; i++) cin >> h[i];

    vector<int> s(n);
    for (int i = 0; i < n; i++) cin >> s[i];

    vector<int> k(n);
    for (int i = 0; i < n; i++) cin >> k[i];

    vector<pair<int, int>> items;

    for (int i = 0; i < n; i++) {
        int copies_left = k[i];
        int bundle_size = 1;

        while (copies_left >= bundle_size) {
            items.push_back({bundle_size * h[i], bundle_size * s[i]});
            copies_left -= bundle_size;
            bundle_size *= 2;
        }
        if (copies_left > 0) {
            items.push_back({copies_left * h[i], copies_left * s[i]});
        }
    }

    vector<int> dp(x + 1, 0);

    for (const auto& item : items) {
        int weight = item.first;
        int value = item.second;
        
        for (int w = x; w >= weight; w--) {
            dp[w] = max(dp[w], dp[w - weight] + value);
        }
    }

    cout << dp[x] << "\n";

    return 0;
}