#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> p(n);
    vector<int> rank(n + 1, -1);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--;
        rank[p[i]] = i;
    }

    string s(n, ' ');
    char current_char = 'a';
    s[p[0]] = current_char;

    for (int i = 0; i < n - 1; i++) {
        int curr = p[i];
        int next = p[i+1];

        int r_curr = (curr + 1 < n) ? rank[curr + 1] : -1;
        int r_next = (next + 1 < n) ? rank[next + 1] : -1;

        if (r_curr > r_next) {
            current_char++;
        }

        if (current_char > 'z') {
            cout << -1 << endl;
            return 0;
        }
        s[next] = current_char;
    }

    cout << s << endl;

    return 0;
}