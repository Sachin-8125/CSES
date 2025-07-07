#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    vector<long>arr(n);
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    long res=arr[0];
    long maxEnding = arr[0];
    for (int i = 1; i < n; i++) {
        maxEnding = max(maxEnding + arr[i], arr[i]);
        res = max(res, maxEnding);
    }
    cout<<res;
}