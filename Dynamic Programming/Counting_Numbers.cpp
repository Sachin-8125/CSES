#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

long long dp[20][10][2][2];

long long countValid(string &num, int idx, int prev_digit, bool leading_zero, bool tight) {
    if (idx == num.length()) {
        return 1;
    }

    if (dp[idx][prev_digit][leading_zero][tight] != -1) {
        return dp[idx][prev_digit][leading_zero][tight];
    }

    int limit = tight ? (num[idx] - '0') : 9;
    long long ans = 0;

    for (int digit = 0; digit <= limit; digit++) {
        if (!leading_zero && digit == prev_digit) {
            continue;
        }

        bool next_leading_zero = leading_zero && (digit == 0);
        bool next_tight = tight && (digit == limit);

        ans += countValid(num, idx + 1, digit, next_leading_zero, next_tight);
    }

    return dp[idx][prev_digit][leading_zero][tight] = ans;
}

long long solve(long long n) {
    if (n < 0) return 0;
    if (n == 0) return 1;

    string num = to_string(n);
    memset(dp, -1, sizeof(dp));

    return countValid(num, 0, 0, true, true);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long a, b;
    if (cin >> a >> b) {
        cout << solve(b) - solve(a - 1) << "\n";
    }

    return 0;
}