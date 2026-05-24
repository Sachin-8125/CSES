#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    string s;
    cin >> s;
    int m = s.length();

    vector<vector<int>> next_state(m + 1, vector<int>(26));

    for (int j = 0; j < m; j++) {
        for (int c = 0; c < 26; c++) {
            char current_char = 'A' + c;
            string temp = s.substr(0, j) + current_char;
            for (int len = min(m, j + 1); len >= 0; len--) {
                if (s.substr(0, len) == temp.substr(temp.size() - len)) {
                    next_state[j][c] = len;
                    break;
                }
            }
        }
    }

    for (int c = 0; c < 26; c++) {
        next_state[m][c] = m;
    }

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    dp[0][0] = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= m; j++) {
            if (dp[i][j] == 0) continue;

            for (int c = 0; c < 26; c++) {
                int nxt = next_state[j][c];
                dp[i + 1][nxt] = (dp[i + 1][nxt] + dp[i][j]) % MOD;
            }
        }
    }

    cout << dp[n][m] << endl;

    return 0;
}
