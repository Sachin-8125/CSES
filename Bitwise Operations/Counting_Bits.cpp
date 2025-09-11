#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    long long n;
    cin >> n;
    
    long long totalSetBits = 0;
    
    for (int k = 0; k < 63; ++k) {
        long long powerOf2_k = 1LL << k;
        long long powerOf2_kplus1 = 1LL << (k + 1);
        
        // Count complete blocks
        totalSetBits += (n / powerOf2_kplus1) * powerOf2_k;
        
        // Count remaining bits in partial block
        long long remainder = n % powerOf2_kplus1;
        totalSetBits += max(0LL, remainder - powerOf2_k + 1);
    }
    
    cout << totalSetBits << endl;
    return 0;
}
