#include <bits/stdc++.h>
using namespace std;

vector <vector<int> >adj(100010);
vector <int> vis(100010);
int v,e,from,to;

void dfs(int u) {
	vis[u] = 1;
	for(auto i: u) {
		if(!vis[i])
			dfs(i);
	}
}
 
int main(){

    cin>>v>>e;
    for(int i=0;i<e;i++){
        cin>>from>>to;
        adj[from].push_back(to);
        adj[to].push_back(from);
    }
    dfs(1);

    return 0;
}
