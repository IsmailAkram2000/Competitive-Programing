#include <bits/stdc++.h>
using namespace std;

map<int,int>parent;
vector<pair<double,pair<int,int> > >adj;
vector<int>x(100010),y(100010);
int v,node;

double dis(int x1,int y1,int x2,int y2){
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

int Find(int x){
    if(x!=parent[x])
        parent[x]=Find(parent[x]);
    return parent[x];
}

void Union(int node1,int node2){
    if(Find(node1)!=Find(node2)){
        parent[Find(node1)]=Find(node2);
    }
}

double Prim(int node) {
    int cnt=0;
    for(int i=0;i<adj.size();i++){
        if(Find(adj[i].second.first)!=Find(adj[i].second.second)){
            if(cnt==v-node)            		  return adj[i].first;
            cnt++;                            Union(adj[i].second.first,adj[i].second.second);
        }
    }
}

int main(){

    cin>>v;
    for(int i=1;i<=v;i++){
        cin>>x[i]>>y[i];
        parent[i]=i;
    }
    for(int i=1;i<v;i++){
        for(int j=i+1;j<=v;j++){
            adj.push_back({dis(x[i],y[i],x[j],y[j]),{i,j}});
        }
    }
    sort(adj.begin(),adj.end());
    cin>>node;
    cout<<fixed<<setprecision(8)<<Prim(node);

    return 0;
}
