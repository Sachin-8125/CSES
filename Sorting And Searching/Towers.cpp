#include<bits/stdc++.h>
using namespace std;
int main(){
    ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n, k;
	cin >> n;
	multiset<int> ans;
	for (int i = 0; i < n; ++i) {
		cin >> k;
		auto it = ans.upper_bound(k);
		if (it == ans.end()) ans.insert(k);
		else {
			ans.erase(it);
			ans.insert(k);
		}
	}
	cout << ans.size();
	return 0;
}