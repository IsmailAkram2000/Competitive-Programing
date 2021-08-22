#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct  node;
extern node *Empty;

struct  node {
	ll val, p, sz, freq;
    node *child[2];

	node() {
		child[0] = child[1] = this;
		val = freq = sz = 0;
		p = INT_MIN;
	}

	node(int v, node *l = Empty, node *r = Empty) {
		child[0] = l, child[1] = r;
		val = v, freq = 1, p = rand();
		push_up();
	}

	void push_up() {
		sz = child[0] -> sz + child[1] -> sz + freq;
	}
};

node *Empty = new node();

struct Treap {

    node *root = Empty;

	void rotate(node *&root, int dir) {
		node *p = root;
		node *q = p -> child[!dir];
		p -> child[!dir] = q -> child[dir];
		q -> child[dir] = p;
		p -> push_up();
		q -> push_up();
		root = q;
	}

	void balance(node *&root) {
		if(root -> child[0] -> p > root -> p)
			rotate(root, 1);
		else if(root -> child[1] -> p > root -> p)
			rotate(root, 0);
	}

	void insert(const ll &v) {
        insert(root, v);
	}

	void insert(node *&root, const ll &v) {
		if(root == Empty) {
			root = new node(v);
			return;
		}
		if(root -> val == v) {
			root -> sz++;
			root -> freq++;
			return;
		}
		if(root -> val > v)
			insert(root -> child[0], v);
		else
			insert(root -> child[1], v);
		root -> push_up();
		balance(root);
	}

	int count(const ll &v) {
        return count(root, v);
	}

	int count(node *&root, const ll &v) {
		if(root == Empty)
			return 0;
		if(root -> val == v)
			return root -> freq;
		if(root -> val > v)
			return count(root -> child[0], v);
		return count(root -> child[1], v);
	}

	void erase(const ll &v) {
        erase(root, v);
	}

	void erase(node *&root, const ll &v) {
		if(root == Empty)
			return;
		if(v < root -> val)
			erase(root -> child[0], v);
		else if(v > root -> val)
			erase(root -> child[1], v);
		else {
			if(root -> freq > 1) {
				root -> freq--;
				root -> sz--;
				return;
			}
			int mxp = root -> child[0] -> p, mxi=0;
			for(int i = 0; i < 2; i++) {
				if(mxp < root -> child[i] -> p) {
					mxp = root -> child[i] -> p;
					mxi = i;
				}
				if(root -> child[i] == Empty) {
					node *tmp = root -> child[!i];
					delete root;
					root = tmp;
					return;
				}
			}
			rotate(root, !mxi);
			erase(root, v);
		}
		root -> push_up();
	}

	const ll &get_by_index(int idx) {
        return get_by_index(root, idx);
	}

	const ll &get_by_index(node *root, int idx) {
		if(idx < root -> child[0] -> sz)
			return get_by_index(root -> child[0], idx);
		int s = root -> child[0] -> sz + root -> freq;
		if(idx >= s)
			return get_by_index(root -> child[1], idx - s);
		return root -> val;
	}

	int lower_bound(const ll &v) {
        return lower_bound(root, v);
	}

	int lower_bound(node *&root, const ll &v) {
		if(root == Empty)
			return 0;
		if(root -> val == v)
			return root -> child[0] -> sz;
		if(root -> val > v)
			return lower_bound(root -> child[0], v);
		return lower_bound(root -> child[1], v) + root -> freq + root -> child[0] -> sz;
	}

	ll size() {
		return root -> sz;
	}

}treap;

int main() {

	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	

	return 0;
}
