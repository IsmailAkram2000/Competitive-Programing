#include<bits/stdc++.h>
using namespace std;
#define INF 1e8

map<int,vector<pair<int,int>>>adj;
vector<int>dis(100010,INF);
int v,e,from,to,w;

bool bellman_ford(){
    dis[1]=0;
    for(int k=1;k<v;k++){
        for(int i=1;i<=v;i++){
            for(int j=0;j<adj[i].size();j++){
                int child=adj[i][j].first,cost=adj[i][j].second;
                if(dis[i]+cost<dis[child]){
                    dis[child]=dis[i]+cost;
                }
            }
        }
    }

    for(int i=1;i<=v;i++){
        for(int j=0;j<adj[i].size();j++){
            int child=adj[i][j].first,cost=adj[i][j].second;
            if(dis[i]+cost<dis[child])
                return 1;
        }
    }

    return 0;
}

int main(){

    cin>>v>>e;
    for(int i=0;i<e;i++){
        cin>>from>>to>>w;
        adj[from].push_back({to,w});
    }
    cout<<bellman_ford();

    return 0;
}
