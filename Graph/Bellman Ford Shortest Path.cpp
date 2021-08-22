#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define INF 1e16

map<ll,vector<pair<ll,ll>>>adj;
vector<ll>dis(100010,INF),visited(100010,0),shortest(100010,0);
queue<int> q;
ll v,e,from,to,w,node;

void Bellman_Ford(int node){

    dis[node]=0,visited[node]=1;
    for(int k=1;k<v;k++){
        for(int i=1;i<=v;i++){
            for(int j=0;j<adj[i].size();j++){
                int child=adj[i][j].first,cost=adj[i][j].second;
                if(dis[i]!=INF && dis[i]+cost<dis[child]){
                    dis[child]=dis[i]+cost,visited[child]=1;
                }
            }
        }
    }

    for(int i=1;i<=v;i++){
        for(int j=0;j<adj[i].size();j++){
            int child=adj[i][j].first,cost=adj[i][j].second;
            if(dis[child]!=INF && dis[i]+cost<dis[child]){
                dis[child]=dis[i]+cost;
                if(!shortest[child]){
                    q.push(child),shortest[child]=INF;
                }
            }
        }
    }

    while(!q.empty()){
        int cur=q.front();      q.pop();
        for(int i=0;i<adj[cur].size();i++){
            int child=adj[cur][i].first;
            if(!shortest[child]){
                q.push(child),shortest[child]=INF;
            }
        }
    }
}

int main() {

    cin>>v>>e;
    for(int i=0;i<e;i++){
        cin>>from>>to>>w;
        adj[from].push_back({to,w});
    }
    cin>>node;
    Bellman_Ford(node);

    for(int i=1;i<=v;i++){
        if(!visited[i])              cout<<"*\n";
        else if(shortest[i]==INF)    cout<<"-\n";
        else                        cout<<dis[i]<<"\n";
    }

    return 0;
}
