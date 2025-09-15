#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    
    vector<int> arr(n + 1);
    vector<int> pos(n + 1);  // pos[i] = position of number i
    
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        pos[arr[i]] = i;
    }
    
    // Calculate initial number of rounds
    int rounds = 1;
    for (int i = 1; i < n; i++) {
        if (pos[i] > pos[i + 1]) {
            rounds++;
        }
    }
    
    // Process m swap operations
    for (int op = 0; op < m; op++) {
        int a, b;
        cin >> a >> b;
        
        // Store pairs that might be affected by the swap
        set<pair<int, int>> affected;
        
        // Add adjacent pairs for elements being swapped
        if (arr[a] > 1) affected.insert({arr[a] - 1, arr[a]});
        if (arr[a] < n) affected.insert({arr[a], arr[a] + 1});
        if (arr[b] > 1) affected.insert({arr[b] - 1, arr[b]});
        if (arr[b] < n) affected.insert({arr[b], arr[b] + 1});
        
        // Remove current inversions
        for (auto& p : affected) {
            if (pos[p.first] > pos[p.second]) {
                rounds--;
            }
        }
        
        // Perform the swap
        swap(arr[a], arr[b]);
        pos[arr[a]] = a;
        pos[arr[b]] = b;
        
        // Add new inversions
        for (auto& p : affected) {
            if (pos[p.first] > pos[p.second]) {
                rounds++;
            }
        }
        
        cout << rounds << "\n";
    }
    
    return 0;
}
