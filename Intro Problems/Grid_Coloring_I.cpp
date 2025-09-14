#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    vector<string> grid(n);
    for (int i = 0; i < n; ++i) {
        cin >> grid[i];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if ((i + j) % 2 == 0) {
                grid[i][j] = (grid[i][j] == 'A' ? 'B' : 'A');
            } else {
                grid[i][j] = (grid[i][j] == 'C' ? 'D' : 'C');
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << grid[i] << "\n";
    }
    return 0;
}