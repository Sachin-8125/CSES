#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<long long> row1(n), row2(n);
    for (int i = 0; i < n; i++) cin >> row1[i];
    for (int i = 0; i < n; i++) cin >> row2[i];

    long long moves = 0;
    long long bal1 = 0, bal2 = 0;

    for (int i = 0; i < n; i++) {

        bal1 += (row1[i] - 1);
        bal2 += (row2[i] - 1);

        
        if ((bal1 > 0 && bal2 < 0) || (bal1 < 0 && bal2 > 0)) {
            long long vertical_move = min(abs(bal1), abs(bal2));
            moves += vertical_move;
            
            if (bal1 > 0) {
                bal1 -= vertical_move;
                bal2 += vertical_move;
            } else {
                bal1 += vertical_move;
                bal2 -= vertical_move;
            }
        }

        moves += abs(bal1) + abs(bal2);
    }

    cout << moves << "\n";

    return 0;
}