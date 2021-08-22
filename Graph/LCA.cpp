#include <bits/stdc++.h>
using namespace std;
#define ll long long

int t, n, q;
vector <int> dep(100010);
vector <vector <int> > adj(100010), dp(19, vector <int> (100010));

void init() {
    for(int i = 0; i <= n; i++) {
        dep[i] = 0;
        adj[i].clear();
    }
    for(int i = 0; i < 19; i++)
        dp[i].resize(n + 1);
}

void dfs(int u, int par = 0) {
    dp[0][u] = par;
    for(auto v: adj[u]) {
        if (v == par)
            continue;
        dep[v] = dep[u] + 1;
        dfs(v, u);
    }
}

int lca(int a, int b) {
    if(dep[a] > dep[b])
        swap(a, b);
    for(int i = 18; i >= 0; i--) {
        if(dep[b] - (1 << i) >= dep[a])
            b = dp[i][b];
    }
    if(b == a)
        return a;
    for(int i = 18; i >= 0; i--) {
        if(dp[i][a] != dp[i][b]) {
            a = dp[i][a];
            b = dp[i][b];
        }
    }
    return dp[0][a];
}

int main() {

    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> t;
    while(t--) {
        cin >> n;
        init();
        for(int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        dfs(1);
        cin >> q;
        while(q--) {
            int u, v;
            cin >> u >> v;
            cout << lca(u, v) << endl;
        }
    }

    return 0;
}
