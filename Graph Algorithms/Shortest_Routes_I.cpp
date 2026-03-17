#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,int> pli;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n,m;
    cin>>n>>m;
    vector<vector<pair<int, int>>> adj(n+1);

    for(int i=0;i<m;i++){
        int a,b,c;
        cin>>a>>b>>c;
        adj[a].push_back({b,c});
    }

    //dijkstra algorithm
    const ll INF = 1e18;
    vector<ll> dist(n + 1, INF);
    dist[1] = 0; // Syrjälä (city 1)
    
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    pq.push({0, 1});

    while(!pq.empty()){
        auto [d,u] = pq.top(); pq.pop();
        if(d>dist[u]) continue; //skip if we have already found a better path
        for(auto [v,w]: adj[u]){
            if(dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    for(int i=1;i<=n;i++){
        cout<<dist[i]<<" ";
    }
    return 0;
}