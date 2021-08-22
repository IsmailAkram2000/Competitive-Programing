#include<bits/stdc++.h>
using namespace std;

vector<vector<int>>adj(100010),GR(100010);
vector<int>visited(100010),order;
int v,e,from,to;

void DFS(int node){
    visited[node]=1;
    for(int i=0;i<GR[node].size();i++){
        if(!visited[GR[node][i]])
            DFS(GR[node][i]);
    }
    order.push_back(node);
}

void explore(int node){
    visited[node]=1;
    for(int i=0;i<adj[node].size();i++){
        if(!visited[adj[node][i]])
            explore(adj[node][i]);
    }
}

int Num_Of_SCC(){
    int result=0;
    for(int i=1;i<=v;i++){
        for(int j=0;j<adj[i].size();j++){
            GR[adj[i][j]].push_back(i);
        }
    }
    for(int i=1;i<=v;i++){
        if(!visited[i])             DFS(i);
    }
    reverse(order.begin(),order.end());
    fill(visited.begin(),visited.end(),0);
    for(int i=0;i<order.size();i++){
        if(!visited[order[i]]){
            explore(order[i]);      result++;
        }
    }
    return result;
}

int main(){

    cin>>v>>e;
    for(int i=0;i<e;i++){
        cin>>from>>to;
        adj[from].push_back(to);
    }
    cout<<Num_Of_SCC();

    return 0;
}
