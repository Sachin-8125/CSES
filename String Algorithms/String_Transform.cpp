#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    if (!(cin >> s)) return 0;

    int n = s.length();
    
    vector<int> count(256, 0);
    for (char c : s) {
        count[c]++;
    }

    vector<int> start(256, 0);
    start['#'] = 0;
    int current_pos = count['#'];
    for (int i = 'a'; i <= 'z'; i++) {
        start[i] = current_pos;
        current_pos += count[i];
    }

    vector<int> lf(n);
    for (int i = 0; i < n; i++) {
        lf[i] = start[s[i]]++;
    }

    string original;
    original.reserve(n - 1);
    
    int curr = 0;
    for (int i = 0; i < n - 1; i++) {
        original += s[curr];
        curr = lf[curr];
    }

    reverse(original.begin(), original.end());
    
    cout << original << "\n";

    return 0;
}