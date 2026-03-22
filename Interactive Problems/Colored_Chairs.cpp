#include <iostream>
#include <string>

using namespace std;

char query(int i) {
    cout << "? " << i << endl;
    char c;
    cin >> c;
    return c;
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    if (!(cin >> n)) return 0;
    
    char c1 = query(1);
    
    // treat chair (n + 1) as chair 1.
    int l = 1;
    int r = n + 1;
    char cl = c1;
    
    // Binary search
    while (r - l > 1) {
        int m = l + (r - l) / 2;
        char cm = query(m);
        
        char expected_cm;
        // If the distance is even, the color should be the same as 'l'
        if ((m - l) % 2 == 0) {
            expected_cm = cl;
        } else {
            expected_cm = (cl == 'R' ? 'B' : 'R');
        }
        if (cm == expected_cm) {
            l = m;
            cl = cm;
        } else {
            r = m;
        }
    }
    cout << "! " << l << endl;
    
    return 0;
}