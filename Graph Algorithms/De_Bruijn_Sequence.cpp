#include <iostream>
#include <vector>
#include <string>

using namespace std;

int n;
vector<bool> seen;
string result;

void dfs(int u) {
    for (int i = 0; i < 2; ++i) {
        int edge = (u << 1) | i;
        if (!seen[edge]) {
            seen[edge] = true;
            dfs(edge & ((1 << (n - 1)) - 1));
            result += (char)('0' + i);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n)) return 0;

    seen.assign(1 << n, false);
    dfs(0);

    result += string(n - 1, '0');
    cout << result << "\n";

    return 0;
}