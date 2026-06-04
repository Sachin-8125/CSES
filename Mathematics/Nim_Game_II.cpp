#include <iostream>
#include <vector>

using namespace std;

void solve() {
    int n;
    cin >> n;
    
    int xor_sum = 0;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        xor_sum ^= (x % 4);
    }
    
    if (xor_sum != 0) {
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