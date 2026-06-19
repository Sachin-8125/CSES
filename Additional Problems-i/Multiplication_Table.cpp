#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long n;
    cin >> n;
    
    long long low = 1, high = n * n;
    long long mid_pos = (n * n + 1) / 2;
    
    while (low < high) {
        long long mid = (low + high) / 2;
        
        long long count = 0;
        for (long long i = 1; i <= n; i++) {
            count += min(n, mid / i);
        }

        if (count >= mid_pos) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    
    cout << high << endl;
    
    return 0;
}