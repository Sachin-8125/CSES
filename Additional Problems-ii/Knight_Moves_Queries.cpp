#include <iostream>
#include <algorithm>

using namespace std;

void solve() {
    long long x, y;
    cin >> x >> y;
    
    long long dx = x - 1;
    long long dy = y - 1;
    
    if (dx > dy) {
        swap(dx, dy);
    }
    
    if (dx == 0 && dy == 0) {
        cout << 0 << "\n";
        return;
    }
    if (dx == 0 && dy == 1) {
        cout << 3 << "\n";
        return;
    }
    if (dx == 1 && dy == 1) {
        cout << 4 << "\n";
        return;
    }
    if (dx == 2 && dy == 2) {
        cout << 4 << "\n";
        return;
    }
    
    long long moves = max((dy + 1) / 2, (dx + dy + 2) / 3);
    
    if (moves % 2 != (dx + dy) % 2) {
        moves++;
    }
    
    cout << moves << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    if (cin >> n) {
        while (n--) {
            solve();
        }
    }
    
    return 0;
}