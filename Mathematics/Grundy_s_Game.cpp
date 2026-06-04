#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

const int MAX_MEMO = 2000;
int grundy[MAX_MEMO + 1];

void precompute_grundy() {
    grundy[0] = grundy[1] = grundy[2] = 0;

    for (int n = 3; n <= MAX_MEMO; ++n) {
        unordered_set<int> transitions;
        for (int i = 1; 2 * i < n; ++i) {
            int g_val = grundy[i] ^ grundy[n - i];
            transitions.insert(g_val);
        }
        int mex = 0;
        while (transitions.count(mex)) {
            mex++;
        }
        grundy[n] = mex;
    }
}

void solve() {
    int n;
    cin >> n;

    if (n > MAX_MEMO) {
        cout << "first\n";
    } else {
        if (grundy[n] > 0) {
            cout << "first\n";
        } else {
            cout << "second\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    precompute_grundy();

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}