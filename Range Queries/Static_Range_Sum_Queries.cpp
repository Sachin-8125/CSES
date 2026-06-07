#include<bits/stdc++.h>
using namespace std;

void solve(vector<long long>& arr, int n){
    for(int i=1;i<n;i++){
        arr[i] += arr[i-1];
    }
}

int main(){
    int n,q;
    cin>>n>>q;

    vector<long long> arr(n);
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }

    solve(arr, n);

    while(q--){
        int a,b;
        cin>>a>>b;
        if(a==1) cout<<arr[b-1]<<endl;
        else cout<<arr[b-1]-arr[a-2]<<endl;
    }

    return 0;
}