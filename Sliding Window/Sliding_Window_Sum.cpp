#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    long x, a, b, c;
    cin >> n >> k;
    cin >> x >> a >> b >> c;

    vector<long> arr(k); 
    long window_sum = 0;
    long xor_result = 0;

    arr[0] = x;
    window_sum = x;
    for (int i = 1; i < k; i++) {
        x = (long(a) * x + b) % c;
        arr[i] = x;
        window_sum += x;
    }
    xor_result = window_sum;

    for (int i = k; i < n; i++) {
        x = (long(a) * x + b) % c;

        window_sum -= arr[i % k];
        window_sum += x;

        arr[i % k] = x;
        xor_result ^= window_sum;
    }
    cout << xor_result << "\n";
    return 0;
}