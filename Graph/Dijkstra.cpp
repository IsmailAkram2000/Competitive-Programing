#include<bits/stdc++.h>
using namespace std;
#define ll long long

vector<pair<ll,ll>> adj[100010];
vector<ll>dis(100010,1e18),par(100010);
ll n,m;

struct edge{
    ll node,w;
    edge(ll node=0,ll w=0):node(node),w(w){}
    bool operator < (edge e)const{
        return w > e.w;
    }
};

void print_path(ll node){
    if(node!=1)         print_path(par[node]);
    cout<<node<<" ";
}

void dijkstra(){
    priority_queue<edge>q;  q.push(edge(1,0));
    while(q.size()){
        auto cur=q.top();   q.pop();
        if(dis[cur.node]!=cur.w)
            continue;
        for(auto i:adj[cur.node]){
            ll child=i.first,w=i.second;
            if(cur.w+w<dis[child]){
                dis[child]=cur.w+w;
                q.push(edge(child,dis[child]));
                par[child]=cur.node;
            }
        }
    }
}

int main(){

    cin>>n>>m;
    for(int i=1;i<=m;i++){
        ll u,v,w;       cin>>u>>v>>w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    dijkstra();
    if(dis[n]==1e18)    return cout<<-1,0;
    print_path(n);

    return 0;
}
