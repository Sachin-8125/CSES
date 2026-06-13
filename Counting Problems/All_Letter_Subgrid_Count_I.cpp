#include <iostream>
#include <algorithm>

using namespace std;

static char grid[3000][3000];
static short last_pos_in_col[3000][26];
static short dist_data[2][3001][26];
static short last_pos_in_row[26];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> grid[i][j];
        }
    }

    for (int j = 0; j < n; ++j) {
        for (int c = 0; c < k; ++c) {
            last_pos_in_col[j][c] = (short)n;
        }
    }
    
    for (int c = 0; c < k; ++c) {
        for (int j = 0; j <= n; ++j) {
            dist_data[0][j][c] = (short)(n + 1);
            dist_data[1][j][c] = (short)(n + 1);
        }
    }

    long long ans = 0;
    for (int i = n - 1; i >= 0; --i) {
        int curr = i % 2;
        int next = (i + 1) % 2;
        
        for (int j = 0; j < n; ++j) {
            int c = grid[i][j] - 'A';
            if (c >= 0 && c < k) {
                last_pos_in_col[j][c] = (short)i;
            }
        }
        
        for (int c = 0; c < k; ++c) last_pos_in_row[c] = (short)n;
        
        for (int j = n - 1; j >= 0; --j) {
            int c_grid = grid[i][j] - 'A';
            if (c_grid >= 0 && c_grid < k) {
                last_pos_in_row[c_grid] = (short)j;
            }
            
            int current_max_d = 0;
            short* d_curr_j = dist_data[curr][j];
            short* d_next_j1 = dist_data[next][j + 1];
            short* l_col_j = last_pos_in_col[j];
            
            for (int c = 0; c < k; ++c) {
                int r_d = (int)last_pos_in_row[c] - j + 1;
                int c_d = (int)l_col_j[c] - i + 1;
                int s_d = (int)d_next_j1[c] + 1;
                
                int d = r_d;
                if (c_d < d) d = c_d;
                if (s_d < d) d = s_d;
                
                d_curr_j[c] = (short)d;
                if (d > current_max_d) current_max_d = d;
            }
            
            int max_s = (n - i < n - j) ? n - i : n - j;
            if (current_max_d <= max_s) {
                ans += (max_s - current_max_d + 1);
            }
        }
    }

    cout << ans << endl;

    return 0;
}