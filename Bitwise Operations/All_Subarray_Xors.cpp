#include <iostream>
#include <vector>

using namespace std;

void fwht(vector<long long>& a) {
    int n = a.size();
    for (int len = 1; 2 * len <= n; len <<= 1) {
        for (int i = 0; i < n; i += 2 * len) {
            for (int j = 0; j < len; j++) {
                long long u = a[i + j];
                long long v = a[i + len + j];
                a[i + j] = u + v;
                a[i + len + j] = u - v;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    int SIZE = 1 << 20; 
    vector<long long> a(SIZE, 0);
    
    a[0] = 1;
    int current_xor = 0;
    bool has_zero = false;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        current_xor ^= x;
        if (a[current_xor] > 0) {
            has_zero = true;
        }
        a[current_xor]++;
    }

    fwht(a);

    for (int i = 0; i < SIZE; i++) {
        a[i] = a[i] * a[i];
    }

    fwht(a);

    vector<int> ans;
    if (has_zero) {
        ans.push_back(0);
    }
    for (int i = 1; i < SIZE; i++) {
        if (a[i] > 0) {
            ans.push_back(i);
        }
    }

    cout << ans.size() << "\n";
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << (i == ans.size() - 1 ? "" : " ");
    }
    cout << "\n";

    return 0;
}