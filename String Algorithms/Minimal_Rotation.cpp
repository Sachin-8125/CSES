#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string minimal_rotation(string s) {
    int n = s.length();
    s += s; 
    int i = 0, ans = 0;
    
    while (i < n) {
        ans = i;
        int j = i + 1, k = i;
        while (j < s.length() && s[k] <= s[j]) {
            k = s[k]<s[j] ? i : k+1;
            j++;
        }
        while (i <= k) {
            i += j - k;
        }
    }
    return s.substr(ans, n);
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    if (cin >> s) {
        cout << minimal_rotation(s) << endl;
    }
    
    return 0;
}
