#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;
typedef pair<int,int> pii;

int N, M, a, b, ds[100001];
vector<pii> ans;

int find(int u){
    if(ds[u] < 0) return u;
    ds[u] = find(ds[u]);
    return ds[u];
}

bool merge(int u, int v){
    u = find(u); v = find(v);
    if(u == v) return false;
    if(ds[u] < ds[v]) swap(u, v);
    ds[v] += ds[u];
    ds[u] = v;
    return true;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    for(int i = 1; i <= N; i++) ds[i] = -1;
    for(int i = 0; i < M; i++){
        cin >> a >> b;
        merge(a, b);
    }

    for(int i = 1; i < N; i++)
        if(merge(i, i+1))
            ans.push_back({i, i+1});

    cout << ans.size() << "\n";
    for(pii P : ans)
        cout << P.first << " " << P.second << "\n";

    return 0;
}