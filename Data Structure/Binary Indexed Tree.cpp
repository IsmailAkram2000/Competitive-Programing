#include <bits/stdc++.h>
using namespace std;
#define ll long long
 
struct BIT_Multiset {
    int N = 1<<22;
    int tree[1<<22];
 
    BIT_Multiset(){
        memset(tree,0,sizeof(tree));
        add(0,-1);
    }
 
    void add(int i,int val){
        for(i++;i<=N;i+=i&-i)
            tree[i-1]+=val;
    }
 
    int get_sum(int i){
        if(i==-1)           return -1;
        int res=0;
        for(i++;i>0;i-=i&(-i))
            res+=tree[i-1];
        return res;
    }
 
    int at(int x){
        int s=0;
        for(int i=N>>1;i;i>>=1)
            if(tree[(s+i)-1]<x)
                x-=tree[(s+=i)-1];
        return s;
    }
 
    void insert(int x){
        add(x,1);
    }
 
    int count(int x){
        return get_sum(x)-get_sum(x-1);
    }
 
    void erase_all(int x){
        add(x,-count(x));
    }
 
    void erase_num(int x,int cnt){
        add(x,-min(cnt,count(x)));
    }
 
    void erase_one(int x){
        if(count(x))        add(x,-1);
    }
 
    int lower_bound(int x){
        return get_sum(x-1)+1;
    }
    int upper_bound(int x){
        return lower_bound(x+1);
    }
 
    int size(){
        return get_sum(N-1)+1;
    }
 
}bit_ms;
 
struct BIT{
    ll N=1e18;
    map<ll,ll>M;
 
    void add(ll i,ll val){
        while(i<=N){
            M[i]+=val;      i+=i&-i;
        }
    }
 
    ll get_sum(ll i){
        ll res=0;
        while(i){
            res+=M[i];      i-=i&-i;
        }
        return res;
    }
 
    ll get_sum_range(ll l,ll r){
        return get_sum(r)-get_sum(l-1);
    }
 
    ll at(ll i){
        return get_sum(i)-get_sum(i-1);
    }
 
}bit;
 
int main(){
 
 
 
    return 0;
}
