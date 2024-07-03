#include<bits/stdc++.h>
using namespace std;
#define ll long long
 
struct segment_tree {
    int sz;
    vector<ll> v;

    void init(int n) {
        sz = 1;
        while (sz < n)
            sz *= 2;
        v.assign(2 * sz, 0);  // Use assign instead of resize and initialize with 0
    }

    void set(int i, int x) {
        i += sz - 1;  // Move to the leaf
        v[i] = x;
        while (i > 1) {
            i /= 2;
            v[i] = max(v[2 * i], v[2 * i + 1]);
        }
    }

    ll query(int l, int r) {
        l += sz - 1;  // Move to the leaf
        r += sz - 1;
        ll res = 0;
        while (l <= r) {
            if (l % 2 == 1) res = max(res, v[l++]);
            if (r % 2 == 0) res = max(res, v[r--]);
            l /= 2;
            r /= 2;
        }
        return res;
    }
}seg;
 
int main(){
 
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
 
    return 0;
}
