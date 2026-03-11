#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 10000005;
int q[MAXN]; 
int arr[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    long long x, a, b, c;
    cin >> x >> a >> b >> c;

    arr[0] = x;
    for (int i = 1; i < n; ++i) {
        arr[i] = (a * arr[i - 1] + b) % c;
    }

    int head = 0; 
    int tail = 0; 
    long long xor_sum = 0;

    for (int i = 0; i < n; ++i) {
        while (head < tail && arr[q[tail - 1]] >= arr[i]) {
            tail--;
        }
        q[tail++] = i;
        if (q[head] <= i - k) {
            head++;
        }
        if (i >= k - 1) {
            xor_sum ^= arr[q[head]];
        }
    }
    cout << xor_sum << endl;
    return 0;
}