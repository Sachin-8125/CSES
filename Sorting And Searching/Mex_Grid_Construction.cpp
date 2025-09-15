#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    // Initialize the grid
    vector<vector<int>> grid(n, vector<int>(n, 0));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // Find numbers that appear to the left in the same row
            set<int> used;
            
            // Add numbers from the left in the same row
            for (int k = 0; k < j; k++) {
                used.insert(grid[i][k]);
            }
            
            // Add numbers from above in the same column
            for (int k = 0; k < i; k++) {
                used.insert(grid[k][j]);
            }
            
            // Find the smallest nonnegative integer not in used
            int candidate = 0;
            while (used.count(candidate)) {
                candidate++;
            }
            
            grid[i][j] = candidate;
        }
    }
    
    // Print the grid
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << grid[i][j];
            if (j < n - 1) cout << " ";
        }
        cout << endl;
    }
    
    return 0;
}
