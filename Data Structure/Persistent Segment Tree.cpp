#include<bits/stdc++.h>
using namespace std;
#define ll long long 
 
struct node {
	int freq;
	node *left, *right;
 
	node() {
		freq = 0;
		left = right = this;
	}
 
	node(int f, node *l = new node, node *r = new node) {
		freq  = f;
		left  = l;
		right = r;
	}
};
 
node *empty = new node; 
 
node *insert(node *root, int val, int lx = -1e9, int rx =1e9) {
	if(val < lx || val > rx) 
		return root;
	if(lx == rx) 
		return new node(root -> freq + 1);
	int mid = lx + (rx - lx) / 2;
	node *l_node = insert(root -> left, val, lx, mid);
	node *r_node = insert(root -> right, val, mid + 1, rx);
	return new node(l_node -> freq + r_node -> freq, l_node, r_node);
}
 
int query(node *l_node, node *r_node, int k, int lx = -1e9, int rx = 1e9) {
	if(lx == rx)
		return lx;
	int mid = lx + (rx - lx) / 2;
	int l_freq = (r_node -> left -> freq) - (l_node -> left -> freq);
	if(l_freq >= k) 
		return query(l_node -> left, r_node -> left, k, lx, mid);
	else
		return query(l_node -> right, r_node -> right, k - l_freq, mid + 1, rx);
}
 
node *roots[100010];
 
int main(){
 
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int n, m, val;
	cin >> n >> m;
	roots[0] = new node;	
	for(int i = 1; i <= n; i++) {
		cin >> val;
		roots[i] = insert(roots[i-1], val);
	}
	while(m--) {
		int l, r, k;
		cin >> l >> r >> k;
		cout << query(roots[l-1], roots[r], k) << "\n";
	}	
 
    return 0;
}
