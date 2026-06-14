#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 3005;
const int MAX_FLAT = MAXN * MAXN;

int n, k;
char grid[MAXN][MAXN];

short LU_flat[MAX_FLAT];
short RD_flat[MAX_FLAT];
char C_flat[MAX_FLAT];

short U_arr[MAXN];
short D_arr[MAXN];
int offset[MAXN * 2];

short BIT[26][MAXN];
long long ans[26];

int head[MAXN];
int nxt[MAXN];
int ev_val[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> k)) return 0;

    for (int i = 0; i < n; ++i) {
        cin >> grid[i];
    }

    offset[0] = 0;
    for (int d = 0; d < 2 * n - 1; ++d) {
        int len = (d < n) ? (d + 1) : (2 * n - 1 - d);
        offset[d + 1] = offset[d] + len;
    }

    for (int r = 0; r < n; ++r) {
        short cur_L = 0;
        for (int c = 0; c < n; ++c) {
            char ch = grid[r][c];
            cur_L = (c > 0 && ch == grid[r][c - 1]) ? cur_L + 1 : 1;
            U_arr[c] = (r > 0 && ch == grid[r - 1][c]) ? U_arr[c] + 1 : 1;
            
            int d = r - c + n - 1;
            int idx = min(r, c);
            int pos = offset[d] + idx;
            
            LU_flat[pos] = min(cur_L, U_arr[c]);
            C_flat[pos] = ch - 'A';
            ans[ch - 'A']++;
        }
    }

    for (int r = n - 1; r >= 0; --r) {
        short cur_R = 0;
        for (int c = n - 1; c >= 0; --c) {
            char ch = grid[r][c];
            cur_R = (c < n - 1 && ch == grid[r][c + 1]) ? cur_R + 1 : 1;
            D_arr[c] = (r < n - 1 && ch == grid[r + 1][c]) ? D_arr[c] + 1 : 1;
            
            int d = r - c + n - 1;
            int idx = min(r, c);
            int pos = offset[d] + idx;
            
            RD_flat[pos] = min(cur_R, D_arr[c]);
        }
    }

    for (int d = 0; d < 2 * n - 1; ++d) {
        int len = (d < n) ? (d + 1) : (2 * n - 1 - d);
        int start_pos = offset[d];

        int node_cnt = 0;
        for (int i = 0; i <= len; ++i) {
            head[i] = 0;
        }

        for (int i = 0; i < len; ++i) {
            int pos = start_pos + i;
            short rd = RD_flat[pos];
            if (rd >= 2) {
                int exp_time = i + rd;
                if (exp_time < len) {
                    ev_val[++node_cnt] = i;
                    nxt[node_cnt] = head[exp_time];
                    head[exp_time] = node_cnt;
                }
            }
        }

        for (int j = 0; j < len; ++j) {
            int p_j = start_pos + j;
            int ch = C_flat[p_j];

            for (int e = head[j]; e; e = nxt[e]) {
                int i = ev_val[e];
                int ch_i = C_flat[start_pos + i];
                short* bit = BIT[ch_i];
                for (int pos_bit = i + 1; pos_bit <= len; pos_bit += pos_bit & -pos_bit) {
                    bit[pos_bit]--;
                }
            }

            if (RD_flat[p_j] >= 2) {
                short* bit = BIT[ch];
                for (int pos_bit = j + 1; pos_bit <= len; pos_bit += pos_bit & -pos_bit) {
                    bit[pos_bit]++;
                }
            }

            short lu = LU_flat[p_j];
            if (lu >= 2) {
                int q_right = j;
                int q_left = j - lu + 2;
                if (q_left <= q_right) {
                    int sum = 0;
                    short* bit = BIT[ch];
                    for (int pos_bit = q_right; pos_bit > 0; pos_bit -= pos_bit & -pos_bit) sum += bit[pos_bit];
                    for (int pos_bit = q_left - 1; pos_bit > 0; pos_bit -= pos_bit & -pos_bit) sum -= bit[pos_bit];
                    ans[ch] += sum;
                }
            }
        }

        for (int i = 0; i < len; ++i) {
            int p_i = start_pos + i;
            short rd = RD_flat[p_i];
            if (rd >= 2 && i + rd >= len) {
                int ch_i = C_flat[p_i];
                short* bit = BIT[ch_i];
                for (int pos_bit = i + 1; pos_bit <= len; pos_bit += pos_bit & -pos_bit) {
                    bit[pos_bit]--;
                }
            }
        }
    }

    for (int i = 0; i < k; ++i) {
        cout << ans[i] << "\n";
    }

    return 0;
}