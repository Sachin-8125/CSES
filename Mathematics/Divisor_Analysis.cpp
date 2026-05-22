#include<bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

const int mod = 1e9+7;

int exp(int x, int y, int mod){
    int ans = 1;
    x = x%mod;
    while (y > 0) {
        if (y&1) ans = ans*x%mod;
        y = y>>1;
        x = x*x%mod;
    }
    return ans;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n; 
    cin>>n;
    int c[3] = {1, 1, 1};
    int flag = 0;
    int sq = 1, num = 1, d = 1;

    for (int i = 0; i < n; i++) {
        int x, y; 
        cin>>x>>y;
        c[0] = c[0]*(y+1)%mod;
        int gsum = (exp(x, y+1, mod) - 1 + mod)%mod*exp(x-1, mod-2, mod)%mod;
        c[1] = c[1]*gsum%mod;
        sq = sq*exp(x, y/2, mod)%mod;
        num = num*exp(x, y, mod)%mod;
        if ((y&1) && flag == 0) {
            d = d*((y+1)/2)%(mod-1);
            flag = 1;
        }
        else d = d*(y+1)%(mod-1);
    }
    c[2]= flag==1 ? exp(num, d, mod) : exp(sq, d, mod);
    cout<<c[0]<<' '<<c[1]<<' '<<c[2];
}