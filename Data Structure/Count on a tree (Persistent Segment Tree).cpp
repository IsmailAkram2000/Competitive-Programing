#include <bits/stdc++.h>
using namespace std;
#define ll long long 
 
int n, m;
vector <int> nodes, idx, dep, weights;
vector <vector <int> > adj;
 
struct node {
 
	int sum;
	node *left, *right;
 
	node() {
		sum = 0;
		left = right = this;
	}
 
	node(int s, node *l = new node, node *r = new node) {
		sum = s;
		left = l;
		right = r;
	}
};
 
vector <node*> roots, parents;
 
struct segtree {
 
	int sz, size;
	vector < pair <int, int> > mn;  
 
	segtree() {
		sz = nodes.size() - 1, size = 1;
		while(size < sz) {
			size *= 2;
		}
		mn.resize(2 * size);
	}	
 
	void build(int cur = 1, int  lx = 1, int rx = -1) {
		if(rx == -1)
			rx = size;
		if(lx == rx) {
			if(lx > sz)
				mn[cur] = {1e9, lx};
			else
				mn[cur] = {dep[nodes[lx]], lx};
			return;
		}
		int mid = (lx + rx) / 2;
		build(2 * cur, lx, mid);
		build(2 * cur + 1, mid + 1, rx);
		mn[cur] = min(mn[2 * cur], mn[2 * cur + 1]);
	}
 
	int get_lca(int l, int r) {
		auto p = get_min(l, r, 1, 1, size);
		return nodes[p.second];		
	}
 
	pair<int,int> get_min(int l, int r, int cur, int lx, int rx) {
		if(lx > r || rx < l)
			return {1e9, 1e9};
		if(lx >= l && rx <= r) 
			return mn[cur];
		int mid = (lx + rx) / 2;
		auto LHS = get_min(l, r, 2 * cur, lx, mid);
		auto RHS = get_min(l, r, 2 * cur + 1, mid + 1, rx);
		return min(LHS, RHS);
	}
 
};
 
void init() {
	weights.resize(n + 1);
	parents.resize(n + 1);
	roots.resize(n + 1);
	idx.resize(n + 1);
	dep.resize(n + 1);
	adj.resize(n + 1);
	roots[0] = new node;
	nodes.push_back(0);
}
 
node *insert(node *root, int val, int lx = INT_MIN, int rx = INT_MAX) {
	if(val < lx || val > rx)
		return root;
	if(lx == rx)
		return new node(root -> sum + 1);
	ll mid = lx + (rx - 0ll - lx) / 2;
	node *ln = insert(root -> left, val, lx, mid);
	node *rn = insert(root -> right, val, mid + 1, rx);
	return new node(ln -> sum + rn -> sum, ln, rn);	
}
 
int query(node *u, node *v, node *lca, node *par_lca, int k, int lx = INT_MIN, int rx = INT_MAX) {
	if(lx == rx)
		return lx;
	ll lsz = u -> left -> sum + v -> left -> sum - lca -> left -> sum - par_lca -> left -> sum;
	ll mid = lx + (rx - 0ll - lx) / 2;
	if(k <= lsz) 
		return query(u -> left, v -> left, lca -> left, par_lca -> left, k, lx, mid);
	return query(u -> right, v -> right, lca -> right, par_lca -> right, k - lsz, mid + 1, rx);
} 
 
void dfs(int u, int par = 0, int lvl = 0) {
	dep[u] = lvl;
	idx[u] = nodes.size();
	nodes.push_back(u);
	parents[u] = roots[par];
	roots[u] = insert(roots[par], weights[u]);
	for(auto v: adj[u]) {
		if(v == par)
			continue;
		dfs(v, u, lvl + 1);
		nodes.push_back(u);		
	}	
}
 
int main() {
 
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin >> n >> m;
	init();
	for(int i = 1; i <= n; i++) 
		cin >> weights[i];
	for(int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	dfs(1);
	segtree seg;
	seg.build();
	while(m--) {
		int u, v, k;
		cin >> u >> v >> k;
		int lca = seg.get_lca(min(idx[u], idx[v]), max(idx[u], idx[v]));
		cout << query(roots[u], roots[v], roots[lca], parents[lca], k) << "\n";
	}
 
   	return 0;
}
