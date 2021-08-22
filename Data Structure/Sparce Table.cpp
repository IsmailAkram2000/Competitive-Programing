#include<bits/stdc++.h>
using namespace std;
#define ll long long
 
int q;
 
struct sparce_table{
    ll n;
    ll dp[20][1000010];
    map<ll,ll>gcd;
 
    ll Log(ll n){
        ll cnt=0;
        while(n){
            n=n>>1;cnt++;
        }
        return cnt-1;
    }
 
    void get_input(){
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>dp[0][i];
        }
    }
 
    void build_max(){
        ll row=Log(n);
        for(int i=1;i<=row;i++){
            ll range=1<<i;
            for(int j=1;j+range-1<=n;j++){
                dp[i][j]=max(dp[i-1][j],dp[i-1][j+(range>>1)]);
            }
        }
    }
 
    void build_min(){
        ll row=Log(n);
        for(int i=1;i<=row;i++){
            ll range=1<<i;
            for(int j=1;j+range-1<=n;j++){
                dp[i][j]=min(dp[i-1][j],dp[i-1][j+(range>>1)]);
            }
        }
    }
 
    void build_gcd(){
        ll row=Log(n);
        for(int i=1;i<=row;i++){
            ll range=1<<i;
            for(int j=1;j+range-1<=n;j++){
                dp[i][j]=__gcd(dp[i-1][j],dp[i-1][j+(range>>1)]);
            }
        }
    }
 
    ll get_max_range(ll l,ll r){
        if(l>r)                 swap(l,r);
        ll row=Log(r-l+1),range=1<<row;
        return max(dp[row][l],dp[row][r-range+1]);
    }
 
    ll get_min_range(ll l,ll r){
        if(l>r)                 swap(l,r);
        ll row=Log(r-l+1),range=1<<row;
        return min(dp[row][l],dp[row][r-range+1]);
    }
 
    ll get_gcd_range(ll l,ll r){
        if(l>r)            swap(l,r);
        ll row=Log(r-l+1),range=1<<row;
        return __gcd(dp[row][l],dp[row][r-range+1]);
    }
 
    void compute_gcd_ranges(){
        for(int l=1;l<=n;l++){
            ll r=n;
            while(r>=l){
                ll cur_gcd=get_gcd_range(l,r),f=l;
                for(int low=l,high=r;low<=high;){
                    ll mid=low+(high-low)/2;
                    if(get_gcd_range(l,mid)==cur_gcd)
                        f=mid,high=mid-1;
                    else
                        low=mid+1;
                }
                gcd[cur_gcd]+=r-f+1;
                r=f-1;
            }
        }
    }
 
    ll count_gcd(ll g){
        return gcd[g];
    }
 
    void print(){
        for(int i=0;i<=Log(n);i++){
            ll range=1<<i;
            for(int j=1;j<=n-range+1;j++){
                cout<<dp[i][j]<<" ";
            }
            cout<<endl;
        }
    }
 
}st;
 
int main(){
 
 
 
	return 0;
}
