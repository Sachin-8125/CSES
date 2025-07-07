#include <bits/stdc++.h>
#define ll long long

using namespace std;

void solve(ll* arr, ll N, ll X)
{
    map<ll, ll> m1;
    bool flag = true;
    for (int i = 0; i < N; i++) {
        if (flag) {
            if (m1.find(X - arr[i]) != m1.end()) {
                cout << (*(m1.find(X - arr[i]))).second
                    << " " << i + 1;
                flag = false;
            }
            m1.insert({ arr[i], i + 1 });
        }
    }
    if (flag)
        cout << "IMPOSSIBLE";
}
int main()
{
    ll N, X;
    cin>>N>>X;
    ll arr[N];
    for(int i=0;i<N;i++){
        cin>>arr[i];
    }
    solve(arr, N, X);
}