#include <bits/stdc++.h>
using namespace std;
#define ll long long
 
struct DSU{
 
    vector<ll>par;
 
    void init(ll n){
    	par.resize(n+1);
        for(int i=1;i<=n;i++){
            par[i]=i;
        }
    }
 
    ll Find(ll v){
        if(v==par[v])
            return v;
        return par[v]=Find(par[v]);
    }
 
    void merge(ll u,ll v){
        par[Find(u)]=Find(v);
    }
 
    bool is_con(ll u,ll v){
        return Find(u)==Find(v);
    }
 
    bool chk(ll n){
        for(int i=2;i<=n;i++)
            if(!is_con(1,i))
                return false;
        return true;
    }
}dsu;
 
int main(){
 
 	
 
    return 0;
}
