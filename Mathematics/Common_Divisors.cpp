#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    const int MAX_X = 1000000;
    vector<int> freq(MAX_X + 1, 0);

    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        freq[x]++;
    }

    for (int gcd = MAX_X; gcd >= 1; --gcd) {
        int multiples = 0;
        for (int j = gcd; j <= MAX_X; j += gcd) {
            multiples += freq[j];
            
            if (multiples >= 2) {
                cout << gcd << "\n";
                return 0;
            }
        }
    }

    return 0;
}