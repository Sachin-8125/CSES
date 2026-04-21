#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> basis(31, 0);
    int size = 0;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;

        for (int j = 30; j >= 0; j--) {
            if (!(x & (1 << j))) continue;

            if (!basis[j]) {
                basis[j] = x;
                size++;
                break;
            }
            x ^= basis[j];
        }
    }

    cout << (1LL << size) << endl;

    return 0;
}