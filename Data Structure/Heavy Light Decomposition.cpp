#include <bits/stdc++.h>
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

struct HLD {
    const int VAL_ON_EDGES = 0; // make 1 if values on edges otherwise 0
    const vector<vector<int>>& adj;
    vector<int> dep, par, root, pos, node, cnt_children, chld;
    int nxt_pos;

    HLD(int n, const vector<vector<int>>& G, int tree_root = 1) : adj(G) {
        nxt_pos = 1;
        dep.resize(n + 1);
        par.resize(n + 1);
        root.resize(n + 1);
        pos.resize(n + 1);
        node.resize(n + 1);
        cnt_children.resize(n + 1);
        chld.resize(n + 1);
        dfs(tree_root);
        build(tree_root);
    }

    void dfs(int v, int p = -1, int d = 0) {
        dep[v] = d;
        par[v] = p;
        cnt_children[v] = 1;
        for (auto u : adj[v]) {
            if (u != p) {
                dfs(u, v, d + 1);
                cnt_children[v] += cnt_children[u];
                if (cnt_children[u] > cnt_children[chld[v]])
                    chld[v] = u;
            }
        }
    }

    void build(int v, bool new_chain = true) {
        root[v] = new_chain ? v : root[par[v]];
        pos[v] = nxt_pos++;
        node[nxt_pos - 1] = v;
        if (chld[v])
            build(chld[v], false);
        for (auto u : adj[v]) {
            if (u != chld[v] && u != par[v])
                build(u, true);
        }
    }

    inline pair<int, int> move_up(int& v) { // move up the chain and also change to next position
        pair<int, int> ans = { pos[root[v]], pos[v] };
        v = par[root[v]];
        return ans;
    }

    inline void make_lower(int& u, int& v) {
        if (dep[root[u]] < dep[root[v]] || (root[u] == root[v] && dep[u] < dep[v])) {
            swap(u, v);
        }
    }

    vector<pair<int, int>> query_path(int u, int v) {
        vector<pair<int, int>> ans;
        while (root[u] != root[v]) {
            make_lower(u, v);
            ans.push_back(move_up(u));
        }
        // add range between u, v
        make_lower(u, v);
        if (!VAL_ON_EDGES) // value on nodes
            ans.push_back({ pos[v], pos[u] });
        else if (u != v) // don't include the root node.
            ans.push_back({ pos[v] + 1, pos[u] });
        return ans;
    }

    pair<int, int> query_subtree(int v) {
        return { pos[v], pos[v] + cnt_children[v] - 1};
    }
};

int main() {
    
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	

    return 0;
}
