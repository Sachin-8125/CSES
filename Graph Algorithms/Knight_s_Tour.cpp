#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int board[8][8];
int dr[] = {-2, -2, -1, -1, 1, 1, 2, 2};
int dc[] = {-1, 1, -2, 2, -2, 2, -1, 1};

bool isValid(int r, int c) {
    return r >= 0 && r < 8 && c >= 0 && c < 8 && board[r][c] == 0;
}

int countMoves(int r, int c) {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        if (isValid(r + dr[i], c + dc[i])) count++;
    }
    return count;
}

bool solve(int r, int c, int move) {
    board[r][c] = move;
    if (move == 64) return true;
    
    vector<pair<int, pair<int, int>>> next;
    for (int i = 0; i < 8; i++) {
        int nr = r + dr[i], nc = c + dc[i];
        if (isValid(nr, nc)) {
            next.push_back({countMoves(nr, nc), {nr, nc}});
        }
    }
    sort(next.begin(), next.end());
    
    for (auto& p : next) {
        if (solve(p.second.first, p.second.second, move + 1)) return true;
    }
    
    board[r][c] = 0;
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int x, y;
    cin >> x >> y;
    
    solve(y - 1, x - 1, 1);
    
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (j > 0) cout << " ";
            cout << board[i][j];
        }
        cout << "\n";
    }
    
    return 0;
}