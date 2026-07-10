#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long y, x;
    if (cin >> y >> x) {
        long long result = (y - 1) ^ (x - 1);
        cout << result << "\n";
    }

    return 0;
}