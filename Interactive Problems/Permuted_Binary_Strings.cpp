#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> a(n, 0);

    for (int j = 0; (1 << j) <= n; ++j) {
        string b = "";
        for (int k = 1; k <= n; ++k) {
            b += (k>>j)&1 ? '1' : '0';
        }
        cout << "? " << b << "\n";
        cout.flush();
        string c;
        cin >> c;
        for (int i = 0; i < n; ++i) {
            if (c[i] == '1') a[i] |= (1 << j);
        }
    }
    
    cout << "!";
    for (int i = 0; i < n; ++i) {
        cout << " " << a[i];
    }
    cout << "\n";
    cout.flush();

    return 0;
}