#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct centroid_decomposition {
    int n, root;
    vector <vector <int> > adj;
    vector <vector <pair <int, int> > > adj2;
    vector <int> sz, done;

    void init(int len, const vector <vector <int> > &G, int tree_root = 1) {
        n = len, root = 0;
        adj = G;
        adj2.resize(n + 1);
        done.resize(n + 1);
        sz.resize(n + 1);
        decompose(1);
    }

    void build_centroid_tree(int u, int par, int cen, int cost) {
        adj2[u].push_back({cen, cost});
        for(auto v: adj[u])
            if (v != par && !done[v])
                build_centroid_tree(v, u, cen, cost + 1);
    }

    int update_sz(int u, int par) {
        sz[u] = 1;
        for(auto v: adj[u])
            if(v != par && !done[v])
                sz[u] += update_sz(v, u);
        return sz[u];
    }

    int get_centroid(int u, int par, int total) {
        int mx = 0, cur = 0;
        for(auto v: adj[u]) {
            if(done[v] || v == par)
                continue;
            if(sz[v] > mx)
                mx = sz[v], cur = v;
        }
        if (mx <= total / 2)
            return u;
        return get_centroid(cur, u, total);
    }

    int decompose(int u, int par = -1) {
        int cen = get_centroid(u, par, update_sz(u, par));
        done[cen] = 1;
        if(par == -1)
            root = cen;
        build_centroid_tree(cen, cen, cen, 0);
        for(auto v: adj[cen]) {
            if(done[v])
                continue;
            decompose(v, cen);
        }
        return cen;
    }

    void print() {
        for(int i = 1; i <= n; i++) {
            cout << i << " : " << " ";
            for(auto j: adj2[i])
                cout << j.first << " " << j.second << ", ";
            cout << endl;
        }
    }

}cd;

int main() {

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, u, v;
    cin >> n;
    vector <vector <int> > adj(n + 1);
    for(int i = 1; i < n; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    cd.init(n, adj);
    cd.print();

    return 0;
}
