#include <iostream>
#include <vector>
#include <string>

using namespace std;

int grid[105][105];
int current_id;

// A mathematically verified perfect tiling of a 5x9 grid using exactly 15 L-trominos
vector<string> p5x9 = {
    "AABBCCDDE",
    "AFFBGCDEE",
    "HHFGGLLNN",
    "HIJJKLMNO",
    "IIJKKMMOO"
};

void fill_2x3(int r, int c) {
    int id1 = current_id++;
    int id2 = current_id++;
    grid[r][c] = id1;
    grid[r][c+1] = id1;
    grid[r+1][c] = id1;
    grid[r+1][c+1] = id2;
    grid[r][c+2] = id2;
    grid[r+1][c+2] = id2;
}

void fill_3x2(int r, int c) {
    int id1 = current_id++;
    int id2 = current_id++;
    grid[r][c] = id1;
    grid[r][c+1] = id1;
    grid[r+1][c] = id1;
    grid[r+1][c+1] = id2;
    grid[r+2][c] = id2;
    grid[r+2][c+1] = id2;
}

void fill_5x9(int r, int c) {
    int ids[256];
    for (char ch = 'A'; ch <= 'O'; ++ch) ids[ch] = current_id++;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 9; ++j) {
            grid[r+i][c+j] = ids[p5x9[i][j]];
        }
    }
}

void fill_9x5(int r, int c) {
    int ids[256];
    for (char ch = 'A'; ch <= 'O'; ++ch) ids[ch] = current_id++;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 9; ++j) {
            grid[r+j][c+i] = ids[p5x9[i][j]];
        }
    }
}

void solve() {
    int n, m;
    cin >> n >> m;

    if ((n * m) % 3 != 0) { cout << "NO\n"; return; }
    if (n == 1 || m == 1) { cout << "NO\n"; return; }
    if (n == 3 && m % 2 != 0) { cout << "NO\n"; return; }
    if (m == 3 && n % 2 != 0) { cout << "NO\n"; return; }

    current_id = 1;

    if (n % 2 == 0 && m % 3 == 0) {
        for (int i = 0; i < n; i += 2) {
            for (int j = 0; j < m; j += 3) fill_2x3(i, j);
        }
    } else if (m % 2 == 0 && n % 3 == 0) {
        for (int i = 0; i < n; i += 3) {
            for (int j = 0; j < m; j += 2) fill_3x2(i, j);
        }
    } else if (n % 6 == 0) {
        for (int i = 0; i < n; i += 2) fill_2x3(i, 0);
        for (int i = 0; i < n; i += 3) {
            for (int j = 3; j < m; j += 2) fill_3x2(i, j);
        }
    } else if (m % 6 == 0) {
        for (int j = 0; j < m; j += 2) fill_3x2(0, j);
        for (int i = 3; i < n; i += 2) {
            for (int j = 0; j < m; j += 3) fill_2x3(i, j);
        }
    } else {
        if (n % 3 == 0) {
            fill_9x5(0, 0);
            for (int i = 0; i < 9; i += 3) {
                for (int j = 5; j < m; j += 2) fill_3x2(i, j);
            }
            for (int i = 9; i < n; i += 6) {
                for (int r = 0; r < 6; r += 2) fill_2x3(i + r, 0);
                for (int j = 3; j < m; j += 2) {
                    for (int r = 0; r < 6; r += 3) fill_3x2(i + r, j);
                }
            }
        } else {
            fill_5x9(0, 0);
            for (int j = 9; j < m; j += 6) {
                for (int c = 0; c < 6; c += 3) fill_2x3(0, j + c);
                for (int c = 0; c < 6; c += 2) fill_3x2(2, j + c);
            }
            for (int i = 5; i < n; i += 2) {
                for (int j = 0; j < m; j += 3) fill_2x3(i, j);
            }
        }
    }

    cout << "YES\n";

    vector<vector<int>> adj(current_id);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int id1 = grid[i][j];
            if (i + 1 < n) {
                int id2 = grid[i+1][j];
                if (id1 != id2) {
                    adj[id1].push_back(id2);
                    adj[id2].push_back(id1);
                }
            }
            if (j + 1 < m) {
                int id2 = grid[i][j+1];
                if (id1 != id2) {
                    adj[id1].push_back(id2);
                    adj[id2].push_back(id1);
                }
            }
        }
    }

    vector<char> color(current_id, 0);
    for (int i = 1; i < current_id; ++i) {
        bool used[26] = {false};
        for (int neighbor : adj[i]) {
            if (color[neighbor] != 0) {
                used[color[neighbor] - 'A'] = true;
            }
        }
        for (int c = 0; c < 26; ++c) {
            if (!used[c]) {
                color[i] = 'A' + c;
                break;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << color[grid[i][j]];
        }
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    if (cin >> t) {
        while (t--) solve();
    }
    return 0;
}