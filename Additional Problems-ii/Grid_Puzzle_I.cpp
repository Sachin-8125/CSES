#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<pair<int, int>> a(n);
    long long sumA = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first;
        a[i].second = i;
        sumA += a[i].first;
    }

    vector<pair<int, int>> b(n);
    long long sumB = 0;
    for (int i = 0; i < n; ++i) {
        cin >> b[i].first;
        b[i].second = i;
        sumB += b[i].first;
    }

    if (sumA != sumB) {
        cout << -1 << "\n";
        return 0;
    }

    sort(a.rbegin(), a.rend());
    vector<string> grid(n, string(n, '.'));

    for (int i = 0; i < n; ++i) {
        int needed = a[i].first;
        int row_idx = a[i].second;

        sort(b.rbegin(), b.rend());

        for (int j = 0; j < needed; ++j) {
            if (b[j].first == 0) {
                cout << -1 << "\n";
                return 0;
            }
            b[j].first--;
            grid[row_idx][b[j].second] = 'X';
        }
    }

    for (int i = 0; i < n; ++i) {
        if (b[i].first > 0) {
            cout << -1 << "\n";
            return 0;
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << grid[i] << "\n";
    }

    return 0;
}