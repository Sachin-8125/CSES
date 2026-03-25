#include<iostream>
#include<vector>
using namespace std;
const long long INF = 1e18;

void solve(){
    int n, m, q;
    cin>>n>>m>>q;

    vector<vector<long long>> dist(n+1, vector<long long>(n+1, INF));

    for(int i=1;i<=n;i++){
        dist[i][i] = 0;
    }

    for(int i=0;i<m;i++){
        int u,v;
        long long w;
        cin>>u>>v>>w;
        if(w<dist[u][v]){
            dist[u][v] = w;
            dist[v][u] = w;
        }
    }
    // Floyd-Warshall
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(dist[i][k]!=INF && dist[k][j]!=INF){
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
    //process queries
    for(int i=0;i<q;i++){
        int a,b;
        cin>>a>>b;
        if(dist[a][b]>=INF){
            cout<<-1<<"\n";
        }else{
            cout<<dist[a][b]<<"\n";
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}