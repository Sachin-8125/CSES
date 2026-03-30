#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long t; 
    if (!(cin >> n >> t)) return 0;

    vector<long long> k(n);
    for (int i = 0; i < n; ++i) {
        cin >> k[i];
    }

    long long low = 1;
    long long high = 1e18; 
    long long ans = high;

    while (low <= high) {
        long long mid = low + (high - low) / 2;
        long long products = 0;
        for (int i = 0; i < n; ++i) {
            products += mid / k[i];
            if (products >= t) break;
        }
        if (products >= t) {
            ans = mid;       
            high = mid - 1;   
        } else {
            low = mid + 1;     
        }
    }

    cout << ans << "\n";

    return 0;
}