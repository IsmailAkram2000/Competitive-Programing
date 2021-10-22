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
 
struct BIT {
    vector<int> tree;
    int n;

    void init(int sz) {
        n = sz + 1;
        tree.assign(n, 0);
    }

    int sum(int r) {
        int ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += tree[r];
        return ret;
    }

    int sum(int l, int r) {
        if(l > r)
            return 0;
        return sum(r) - sum(l - 1);
    }

    void add(int idx, int val) {
        for (; idx < n; idx = idx | (idx + 1))
            tree[idx] += val;
    }

}bit;
 
int main(){
 
 
 
    return 0;
}
