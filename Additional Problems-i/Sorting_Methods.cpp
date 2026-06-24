#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct BIT {
    int n;
    vector<int> tree;
    BIT(int n) : n(n), tree(n + 1, 0) {}
    
    void add(int i, int delta) {
        for (; i <= n; i += i & -i) {
            tree[i] += delta;
        }
    }
    
    int query(int i) {
        int sum = 0;
        for (; i > 0; i -= i & -i) {
            sum += tree[i];
        }
        return sum;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    long long inversions = 0;
    BIT bit(n);
    for (int i = n - 1; i >= 0; --i) {
        inversions += bit.query(a[i] - 1);
        bit.add(a[i], 1);
    }

    int cycles = 0;
    vector<bool> vis(n + 1, false);
    for (int i = 0; i < n; ++i) {
        if (!vis[a[i]]) {
            cycles++;
            int curr = a[i];
            while (!vis[curr]) {
                vis[curr] = true;
                curr = a[curr - 1];
            }
        }
    }
    int swaps = n - cycles;

    vector<int> lis;
    for (int i = 0; i < n; ++i) {
        auto it = lower_bound(lis.begin(), lis.end(), a[i]);
        if (it == lis.end()) {
            lis.push_back(a[i]);
        } else {
            *it = a[i];
        }
    }
    int move_anywhere = n - lis.size();

    int target = n;
    for (int i = n - 1; i >= 0; --i) {
        if (a[i] == target) {
            target--;
        }
    }
    int move_front = target;

    cout << inversions << " " << swaps << " " << move_anywhere << " " << move_front << "\n";

    return 0;
}