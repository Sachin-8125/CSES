#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

typedef long long ll;

ll fact[21];

void precompute() {
    fact[0] = 1;
    for (int i = 1; i <= 20; i++) {
        fact[i] = fact[i - 1] * i;
    }
}

void solve_kth() {
    int n;
    ll k;
    cin >> n >> k;
    vector<int> nums(n);
    iota(nums.begin(), nums.end(), 1);
    vector<int> res;
    k--; // 0-indexed
    for (int i = 0; i < n; i++) {
        int idx = k / fact[n - 1 - i];
        res.push_back(nums[idx]);
        nums.erase(nums.begin() + idx);
        k %= fact[n - 1 - i];
    }
    for (int i = 0; i < n; i++) {
        cout << res[i] << (i == n - 1 ? "" : " ");
    }
    cout << "\n";
}

void solve_rank() {
    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; i++) cin >> p[i];
    vector<int> nums(n);
    iota(nums.begin(), nums.end(), 1);
    ll rank = 1;
    for (int i = 0; i < n; i++) {
        int idx = 0;
        while (nums[idx] != p[i]) idx++;
        rank += (ll)idx * fact[n - 1 - i];
        nums.erase(nums.begin() + idx);
    }
    cout << rank << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    precompute();
    int t;
    cin >> t;
    while (t--) {
        int type;
        cin >> type;
        if (type == 1) {
            solve_kth();
        } else {
            solve_rank();
        }
    }
    return 0;
}
