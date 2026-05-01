#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(),x.end()
#define IOS ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);

vector<int> prefix(string s) {
    int n = s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

void solve(){
    string s;
    cin>>s;
    vector<int> v = prefix(s);
    vector<int> ans;
    int j = v.back();
    while(j>0){
        ans.pb(j);
        j = v[j-1];
    }
    sort(all(ans));
    for (auto i: ans) cout<<i<<" ";
}    

signed main(){
    IOS;
    solve();
}