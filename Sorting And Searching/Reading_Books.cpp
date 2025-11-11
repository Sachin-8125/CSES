#include <iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main() {
    int n;
    cin >> n; 
    vector<long long> t(n);
    long long mx = 0, sum=0;
    for(int i=0;i<n;i++){
        cin>>t[i];
        mx = max(mx,t[i]);
        sum+=t[i];
    }
    cout<<max(sum,2*mx)<<endl;
}