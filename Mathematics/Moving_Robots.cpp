#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    cin >> k;

    const int N = 8;

    long double emptyProb[N][N];

    for (int r = 0; r < N; r++)
        for (int c = 0; c < N; c++)
            emptyProb[r][c] = 1.0L;

    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    for (int sr = 0; sr < N; sr++) {
        for (int sc = 0; sc < N; sc++) {

            long double dp[N][N] = {};
            long double next_dp[N][N] = {};

            dp[sr][sc] = 1.0L;

            for (int step = 0; step < k; step++) {

                for (int r = 0; r < N; r++)
                    for (int c = 0; c < N; c++)
                        next_dp[r][c] = 0.0L;

                for (int r = 0; r < N; r++) {
                    for (int c = 0; c < N; c++) {
                        if (dp[r][c] == 0.0L) continue;

                        int moves = 0;
                        for (int d = 0; d < 4; d++) {
                            int nr = r + dr[d];
                            int nc = c + dc[d];
                            if (nr >= 0 && nr < N && nc >= 0 && nc < N)
                                moves++;
                        }

                        for (int d = 0; d < 4; d++) {
                            int nr = r + dr[d];
                            int nc = c + dc[d];
                            if (nr >= 0 && nr < N && nc >= 0 && nc < N) {
                                next_dp[nr][nc] += dp[r][c] / moves;
                            }
                        }
                    }
                }

                for (int r = 0; r < N; r++)
                    for (int c = 0; c < N; c++)
                        dp[r][c] = next_dp[r][c];
            }

            for (int r = 0; r < N; r++) {
                for (int c = 0; c < N; c++) {
                    emptyProb[r][c] *= (1.0L - dp[r][c]);
                }
            }
        }
    }

    long double result = 0.0L;
    for (int r = 0; r < N; r++)
        for (int c = 0; c < N; c++)
            result += emptyProb[r][c];

    cout << fixed << setprecision(6) << (double)result << "\n";

    return 0;
}