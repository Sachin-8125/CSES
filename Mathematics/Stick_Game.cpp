#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<int> moves(k);
    for (int i = 0; i < k; ++i) {
        cin >> moves[i];
    }

    vector<bool> dp(n + 1, false);

    for (int i = 1; i <= n; ++i) {
        for (int move : moves) {
            if (i >= move && !dp[i - move]) {
                dp[i] = true;
                break;
            }
        }
    }

    string result = "";
    for (int i = 1; i <= n; ++i) {
        if (dp[i]) {
            result += 'W';
        } else {
            result += 'L';
        }
    }

    cout << result << "\n";

    return 0;
}
