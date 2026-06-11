#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n, k;
    if (!(cin >> n >> k)) return 0;

    int left = 1;
    int right = n;

    for (int i = 1; i <= n; ++i) {
        long long rem = n - i; 

        if (k >= rem) {
            cout << right << (i == n ? "" : " ");
            k -= rem;
            right--;
        } else {
            cout << left << (i == n ? "" : " ");
            left++;
        }
    }
    cout << "\n";

    return 0;
}