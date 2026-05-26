#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    if (!(cin >> s)) return 0;

    int n = s.length();
    vector<long long> last(26, 0);
    long long total = 1; 

    for (char c : s) {
        int idx = c - 'a';
        long long curr = total;
        
        total = (total * 2) % MOD;
        total = (total - last[idx] + MOD) % MOD;
        
        last[idx] = curr;
    }
    cout << (total - 1 + MOD) % MOD << endl;
    return 0;
}