#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,m;
    cin>>n>>m;
    vector<vector<int>> adj(n+1);

    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> vis(n+1, -1);
    
    for(int i=1; i<=n; i++){
        if(vis[i]!=-1) continue;
        //bfs
        queue<int> q;
        vis[i] = 1;
        q.push(i);

        while(!q.empty()){
            int u=q.front(); q.pop();
            for(int v: adj[u]){
                if(vis[v]==-1){
                    vis[v] = vis[u]==1?2:1;
                    q.push(v);
                }else if(vis[v]==vis[u]){
                    cout<<"IMPOSSIBLE\n";
                    return 0;
                }
            }
        }
    }
    //print teams
    for(int i=1;i<=n;i++){
        cout<<vis[i]<<" ";
    }
    return 0;
}