#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while (T--) {
        int n, a, b;
        cin >> n >> a >> b;
        if (a == 0 && b == 0) {
            cout << "YES\n";
            for (int i = 0; i < 2; i++) {
                for (int j = 1; j <= n; j++) {
                    cout << j << (j == n ? '\n' : ' ');
                }
            }
            continue;
        }
        if (a + b > n || a == 0 || b == 0) {
            cout << "NO\n";
            continue;
        }
        cout << "YES\n";
        int ties = n - a - b;
        vector<int> xs(n + 1);
        for (int i = 1; i <= a + b; i++) {
            int pos = (i + b - 1) % (a + b) + 1;
            xs[pos] = i;
        }
        
        for (int i = a + b + 1; i <= n; i++) {
            xs[i] = i;
        }
        for (int i = 1; i <= n; i++) {
            cout << i << (i == n ? '\n' : ' ');
        }
        for (int i = 1; i <= n; i++) {
            cout << xs[i] << (i == n ? '\n' : ' ');
        }
    }
    return 0;
}