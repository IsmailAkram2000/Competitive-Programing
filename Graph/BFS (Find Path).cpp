#include <bits/stdc++.h>
using namespace std;

vector<vector<int> >adj(100010);
vector<int>depth(100010,-1),par(100010,-1),path;
queue<int>q;
int v,e,from,to;

vector<int> BFS(int start,int end){
	int cur=start,len=1,size=1;
	bool ok=true;
	q.push(start),depth [start]=0;
	for(;ok && !q.empty();len++,size=q.size()){
        while(ok && size--){
            cur=q.front(),q.pop();
            for(int i=0;i<adj[cur].size() && ok;i++){
            	int child=adj[cur][i];
                if(depth[child]==-1){
                    q.push(child);
                    depth[child]=len;
                    par[child]=cur;
                }
                if(child==end)	         ok=false;
            }
        }
	}
	while(end!=-1){
        path.push_back(end);
        end=par[end];
	}
	return path;
}

int main(){

    cin>>v>>e;
    for(int i=0;i<e;i++){
        cin>>from>>to;
        adj[from].push_back(to);
        adj[to].push_back(from);
    }
    cin>>from>>to;
    BFS(from,to);
    if(path.size()==1){
        cout<<-1;
        return 0;
    }
    for(int i=path.size()-1;i>=0;i--){
        cout<<path[i]<<" ";
    }

    return 0;
}
