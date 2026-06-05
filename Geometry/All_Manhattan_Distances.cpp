#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void print128(__int128_t n) {
    if (n == 0) {
        cout << 0 << "\n";
        return;
    }
    string s = "";
    while (n > 0) {
        s += (char)('0' + (n % 10));
        n /= 10;
    }
    reverse(s.begin(), s.end());
    cout << s << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    if (!(cin >> n)) return 0;
    
    vector<long long> x(n), y(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
    }
    
    sort(x.begin(), x.end());
    sort(y.begin(), y.end());
    
    __int128_t total_distance = 0;
    
    for (int i = 0; i < n; ++i) {
        __int128_t rank_multiplier = 2LL * i - (n - 1);
        total_distance += (__int128_t)x[i] * rank_multiplier;
        total_distance += (__int128_t)y[i] * rank_multiplier;
    }
    
    print128(total_distance);
    
    return 0;
}