#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct lazy_segment_tree {
    int sz;
    vector<ll> v, lazy;

    void init(int n) {
        sz = 1;
        while (sz < n)
            sz *= 2;
        v.assign(2 * sz, 0);
        lazy.assign(2 * sz, 0);
    }

    void push_down(int cur, int l, int r) {
        if (lazy[cur] != 0) {
            v[cur] += lazy[cur] * (r - l + 1); // Update the current node
            if (l != r) {
                lazy[2 * cur] += lazy[cur]; // Propagate to left child
                lazy[2 * cur + 1] += lazy[cur]; // Propagate to right child
            }
            lazy[cur] = 0;
        }
    }

    void set(int lx, int rx, int cur, int l, int r) {
        push_down(cur, l, r);
        if (lx > r || rx < l) return;
        if (lx <= l && rx >= r) {
            lazy[cur]++;
            push_down(cur, l, r);
            return;
        }
        int mid = (l + r) / 2;
        set(lx, rx, 2 * cur, l, mid);
        set(lx, rx, 2 * cur + 1, mid + 1, r);
        v[cur] = v[2 * cur] + v[2 * cur + 1];
    }

    ll query(int lx, int rx, int cur, int l, int r) {
        push_down(cur, l, r);
        if (lx > r || rx < l) return 0;
        if (lx <= l && rx >= r) return v[cur];
        int mid = (l + r) / 2;
        ll left = query(lx, rx, 2 * cur, l, mid);
        ll right = query(lx, rx, 2 * cur + 1, mid + 1, r);
        return left + right;
    }

    void set(int l, int r) {
        if (l > r) swap(l, r);
        set(l, r, 1, 1, sz);
    }

    ll query(int l, int r) {
        if (l > r) swap(l, r);
        return query(l, r, 1, 1, sz);
    }

    int get_node(int cur) {
        return node[cur];
	}
}seg;

struct HLD {
    const int VAL_ON_EDGES = 1; // make 1 if values on edges otherwise 0
    const vector<vector<int>> &adj;
    vector<int> dep, par, root, pos, cntChildren, chld;
    int nxt_pos;

    HLD(int n, const vector<vector<int>> &G, int treeRoot = 1) : adj(G) {
        nxt_pos = 1;
        dep.resize(n + 5);
        par.resize(n + 5);
        root.resize(n + 5);
        pos.resize(n + 5);
        cntChildren.resize(n + 5);
        chld.resize(n + 5);
        init(treeRoot);
        build(treeRoot);
    }

    void init(int v, int p = -1, int d = 0) {
        dep[v] = d;
        par[v] = p;
        cntChildren[v] = 1;
        for (int u : adj[v]) {
            if (u != p) {
                init(u, v, d + 1);
                cntChildren[v] += cntChildren[u];
                if (cntChildren[u] > cntChildren[chld[v]])
                    chld[v] = u;
            }
        }
    }

    void build(int v, bool newChain = true) {
        root[v] = newChain ? v : root[par[v]];
        pos[v] = nxt_pos++;
        if (chld[v])
            build(chld[v], false);
        for (int u : adj[v]) {
            if (u != chld[v] && u != par[v])
                build(u, true);
        }
    }

    inline pair<int, int> moveUp(int &v) { // move up the chain and also change to next position
        pair<int, int> ans = {pos[root[v]], pos[v]};
        v = par[root[v]];
        return ans;
    }

    inline void makeULower(int &u, int &v) {
        if (dep[root[u]] < dep[root[v]] || (root[u] == root[v] && dep[u] < dep[v])) {
            swap(u, v);
        }
    }

    vector<pair<int, int>> queryPath(int u, int v) {
        // return all ranges to query in segment tree
        vector<pair<int, int>> ans;
        while (root[u] != root[v]) {
            makeULower(u, v);
            ans.push_back(moveUp(u));
        }
        // add range between u, v
        makeULower(u, v);
        if (!VAL_ON_EDGES) // value on nodes
            ans.push_back({pos[v], pos[u]});
        else if (u != v) // don't include the root node.
            ans.push_back({pos[v] + 1, pos[u]});
        return ans;
    }

    int get_node(int cur) {
        return node[cur];
    }
};

int main() {

    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);


    return 0;
}
