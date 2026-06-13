#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<string> grid(n);
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    vector<long long> result(26, 0);
    vector<int> dp(n, 0);

    for (int i = 0; i < n; i++) {
        vector<pair<int, int>> stack;
        long long curr = 0;

        for (int j = 0; j < n; j++) {
            if (i > 0 && grid[i][j] == grid[i-1][j]) {
                dp[j]++;
            } else {
                dp[j] = 1;
            }

            if (j > 0 && grid[i][j] != grid[i][j-1]) {
                stack.clear();
                curr = 0;
            }

            int wid = 1;
            while (!stack.empty() && stack.back().first >= dp[j]) {
                wid += stack.back().second;
                curr -= 1LL * stack.back().first * stack.back().second;
                stack.pop_back();
            }

            stack.push_back({dp[j], wid});
            curr += 1LL * dp[j] * wid;

            result[grid[i][j] - 'A'] += curr;
        }
    }

    for (int i = 0; i < k; i++) {
        cout << result[i] << "\n";
    }

    return 0;
}