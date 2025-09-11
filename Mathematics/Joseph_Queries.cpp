#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin>>t;
    while(t--){
        int n, k;
        cin >> n >> k; // n = children, k = skip count
        set<int> children;
        for (int i = 1; i <= n; ++i)
            children.insert(i);

        int idx = 0;
        while (!children.empty()) {
            idx = (idx + k - 1) % children.size();
            auto it = children.begin();
            advance(it, idx);
            cout << *it << " ";
            children.erase(it);
        }
        cout << endl;
    }
}
