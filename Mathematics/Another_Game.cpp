#include <iostream>
#include <vector>

using namespace std;

void solve() {
    int n;
    cin >> n;
    
    bool first_wins = false;
    for (int i = 0; i < n; i++) {
        long long x;
        cin >> x;

        if (x % 2 != 0) {
            first_wins = true;
        }
    }
    
    if (first_wins) {
        cout << "first\n";
    } else {
        cout << "second\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    
    return 0;
}