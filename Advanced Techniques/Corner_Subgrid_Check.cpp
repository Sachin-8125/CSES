#include <iostream>
#include <vector>
#include <string>

using namespace std;

int8_t seen[3005][3005];
int16_t col_pool[9005000];
int16_t* char_cols[26][3005];
int char_sz[26][3005];
int char_counts[26][3005];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    if (!(cin >> n >> k)) return 0;
    
    vector<string> grid(n);
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
        for (int j = 0; j < n; j++) {
            int c = grid[i][j] - 'A';
            if (c >= 0 && c < k) {
                char_counts[c][i]++;
            }
        }
    }
    
    int16_t* ptr = col_pool;
    for (int c = 0; c < k; c++) {
        for (int i = 0; i < n; i++) {
            char_cols[c][i] = ptr;
            ptr += char_counts[c][i];
        }
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int c = grid[i][j] - 'A';
            if (c >= 0 && c < k) {
                char_cols[c][i][char_sz[c][i]++] = j;
            }
        }
    }
    
    for (int c_idx = 0; c_idx < k; c_idx++) {
        bool found = false;
        int8_t check_val = c_idx + 1;
        
        for (int i = 0; i < n; i++) {
            int sz = char_sz[c_idx][i];
            int16_t* cols = char_cols[c_idx][i];
            for (int x = 0; x < sz; x++) {
                int16_t cx = cols[x];
                int8_t* row_seen = seen[cx];
                for (int y = x + 1; y < sz; y++) {
                    int16_t cy = cols[y];
                    if (row_seen[cy] == check_val) {
                        found = true;
                        goto end_search;
                    }
                    row_seen[cy] = check_val;
                }
            }
        }
    end_search:
        if (found) cout << "YES\n";
        else cout << "NO\n";
    }
    
    return 0;
}