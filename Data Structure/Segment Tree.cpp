#include<bits/stdc++.h>
using namespace std;
#define ll long long
 
struct segment_tree{
 
	int sz;
	vector<int> v;
 
	void init(int n) {
		sz = 1;
		while(sz < n)
			sz *= 2;
		v.resize(2 * sz);
	}
 
	void set(int i, int x) {
		set(i, x, 1, 1, sz);
	}
 
	void set(int i, int x, int cur, int l, int r) {
		if (l == r) {
			v[cur] = x;
			return;
		}
		int mid = (l + r) / 2;
		if (i <= mid) 
			set(i, x, 2 * cur, l, mid);
		else 
			set(i, x, 2 * cur + 1, mid + 1, r);
		v[cur] = v[2 * cur] + v[2 * cur + 1];
	}  
 
	ll sum(int l, int r) {
		return sum(l, r, 1, 1, sz); 
	}
 
	ll sum(int l, int r, int cur, int lx, int rx) {
		 if(lx > r || rx < l)	
			 return 0;
		 if(lx >= l && rx <= r) 
			 return v[cur];
		 int mid = (lx + rx) / 2;
		 ll s1 = sum(l, r, 2 * cur, lx, mid);
		 ll s2 = sum(l, r, 2 * cur + 1, mid + 1, rx);
		 return s1 + s2;
	}
 
}seg;
 
int main(){
 
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int n, q, x, op;
	cin >> n >> q;
	seg.init(n);
	for(int i = 1; i <= n; i++) {
		cin >> x;
		seg.set(i, x);
	}
	while(q--) {
		cin >> op;
		if (op == 1) {
			int i, a;
			cin >> i >> a;
			seg.set(++i, a);
		}else {
			int l, r;
			cin >> l >> r;
			cout << seg.sum(l + 1, r) << "\n";
		}
	}
 
    return 0;
}
