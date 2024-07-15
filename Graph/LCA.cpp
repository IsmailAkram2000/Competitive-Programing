#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct LCA {
    int N, LG;
    vector<vector<int>> adj;
    vector<vector<int>> par;
    vector<int> dep, sz;

    // Constructor to initialize the LCA struct with the size of the tree
    LCA(int n) {
        N = n;
        LG = log2(n) + 1;
        adj.resize(N + 1);
        par.resize(N + 1, vector<int>(LG + 1));
        dep.resize(N + 1);
        sz.resize(N + 1);
    }

    // Depth-first search to preprocess LCA
    void dfs(int u, int p = 0) {
        par[u][0] = p;
        dep[u] = dep[p] + 1;
        sz[u] = 1;
        for (int i = 1; i <= LG; i++) par[u][i] = par[par[u][i - 1]][i - 1];
        for (auto v : adj[u]) {
            if (v != p) {
                dfs(v, u);
                sz[u] += sz[v];
            }
        }
    }

    // Function to find the lowest common ancestor (LCA) of nodes u and v
    int lca(int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);
        for (int k = LG; k >= 0; k--) {
            if (dep[par[u][k]] >= dep[v]) u = par[u][k];
        }
        if (u == v) return u;
        for (int k = LG; k >= 0; k--) {
            if (par[u][k] != par[v][k]) {
                u = par[u][k];
                v = par[v][k];
            }
        }
        return par[u][0];
    }

    // Function to find the k-th ancestor of node u
    int kth(int u, int k) {
        assert(k >= 0);
        for (int i = 0; i <= LG; i++) {
            if (k & (1 << i)) u = par[u][i];
        }
        return u;
    }

    // Function to find the distance between nodes u and v
    int dist(int u, int v) {
        int l = lca(u, v);
        return dep[u] + dep[v] - (dep[l] << 1);
    }

    // Function to find the k-th node from u to v (0th node is u)
    int go(int u, int v, int k) {
        int l = lca(u, v);
        int d = dep[u] + dep[v] - (dep[l] << 1);
        assert(k <= d);
        if (dep[l] + k <= dep[u]) return kth(u, k);
        k -= dep[u] - dep[l];
        return kth(v, dep[v] - dep[l] - k);
    }
};

int main() {
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    int n, q, u, v;
    cin >> n >> q;

    // Initialize LCA solver with the size of the tree
    LCA lca_solver(n);

    // Read the tree structure
    for (int i = 2; i <= n; i++) {
        cin >> u >> v;
        lca_solver.adj[u].push_back(v);
        lca_solver.adj[v].push_back(u);
    }

    // Preprocess the tree for LCA queries
    lca_solver.dfs(1);

    // Handle queries
    while (q--) {
        cin >> u >> v;
        cout << lca_solver.lca(u, v) << "\n";
    }

    return 0;
}
