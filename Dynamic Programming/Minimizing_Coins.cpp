#include<iostream>
#include<vector>
#include<climits>
using namespace std;
int main(){
    int n,s;
    cin>>n>>s;
    vector<int> arr(n);
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    const int MOD = 1e9+7;
    vector<int> dp(s+1,MOD);
    dp[0]=0;
    for(int i=1;i<=s;++i){
        for(int c: arr){
            if(i-c>=0 && dp[i-c]!=MOD){
                dp[i] = min(dp[i],dp[i-c]+1);
            }
        }
    }
    cout << (dp[s] == MOD ? -1 : dp[s]) << endl;
    return 0;
}