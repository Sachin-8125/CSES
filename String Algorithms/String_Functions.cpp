#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

vector<int> calculate_z(const string& s) {
    int n = s.length();
    vector<int> z(n, 0);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

vector<int> calculate_pi(const string& s) {
    int n = s.length();
    vector<int> pi(n, 0);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1];
        }
        if (s[i] == s[j]) {
            j++;
        }
        pi[i] = j;
    }
    return pi;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    if (!(cin >> s)) return 0;

    vector<int> z = calculate_z(s);
    vector<int> pi = calculate_pi(s);

    for (int i = 0; i < (int)z.size(); i++) {
        cout << z[i] << (i == (int)z.size() - 1 ? "" : " ");
    }
    cout << "\n";

    for (int i = 0; i < (int)pi.size(); i++) {
        cout << pi[i] << (i == (int)pi.size() - 1 ? "" : " ");
    }
    cout << "\n";

    return 0;
}