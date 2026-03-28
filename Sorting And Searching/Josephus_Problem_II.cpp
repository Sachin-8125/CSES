#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    vector<int> tree;
    int n;
    Fenwick(int n) : n(n), tree(n + 1) {}
    
    void add(int i, int v) {
        for (; i <= n; i += i & -i) tree[i] += v;
    }
    
    int sum(int i) {
        int res = 0;
        for (; i > 0; i -= i & -i) res += tree[i];
        return res;
    }
    
    int findKth(int k) {
        int idx = 0;
        int bitMask = 1 << (31 - __builtin_clz(n)); // largest power of 2 <= n
        for (int d = bitMask; d; d >>= 1) {
            int next = idx + d;
            if (next <= n && tree[next] < k) {
                k -= tree[next];
                idx = next;
            }
        }
        return idx + 1;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    long long k;
    cin >> n >> k;
    
    Fenwick fw(n);
    for (int i = 1; i <= n; i++) fw.add(i, 1);
    
    int pos = 0; 
    
    for (int remaining = n; remaining > 0; remaining--) {
        pos = (pos + k) % remaining;
        int person = fw.findKth(pos + 1);
        cout << person;
        if (remaining > 1) cout << ' ';
        fw.add(person, -1); 
    }
    cout << '\n';
    
    return 0;
}


