#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<long long> freq(n, 0);
    long long sum = 0;
    freq[0] = 1;  // Empty prefix has remainder 0
    
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        sum = (sum + x) % n;
        if (sum < 0) sum += n;  // Handle negative remainders
        freq[sum]++;
    }
    
    long long result = 0;
    for (long long f : freq) {
        result += f * (f - 1) / 2;  // Count pairs with same remainder
    }
    
    cout << result << "\n";
    return 0;
}