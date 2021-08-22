#include <bits/stdc++.h>
using namespace std;

vector<vector<int> >adj(100010);
vector<int>len(100010,-1);
queue<int>q;
int v,e,from,to;

vector<int> bfs(int start){
	q.push(start),len[start]=0;
	int dep=1,sz=1,cur;
	for(;!q.empty();dep++,sz=q.size()){
        while(sz--){
            cur=q.front(),q.pop();
            for(int i=0;i<adj[cur].size();i++){
                int child=adj[cur][i];
                if(len[child]==-1){
                    q.push(child),len[child]=dep;
                }
            }
        }
	}
	return len;
}

int main(){

    cin>>v>>e;
    for(int i=0;i<e;i++){
        cin>>from>>to;
        adj[from].push_back(to);
        adj[to].push_back(from);
    }
    bfs(1);
    for(int i=1;i<=v;i++){
        cout<<len[i]<<" ";
    }

    return 0;
}
