#include <bits/stdc++.h>
using namespace std;
#define ll long long

vector <vector <int> > adj(100010), dp(19, vector <int> (100010));
vector <int> dep(100010);

void dfs(int u, int par = 0) {
    dp[0][u] = par;
    for (int i = 1; i < 19; i++)
        dp[i][u] = dp[i - 1][dp[i - 1][u]];
    for(auto v: adj[u]) {
        if (v == par)
            continue;
        dep[v] = dep[u] + 1;
        dfs(v, u);
    }
}

ll lca(ll a, ll b) {
    if(dep[a] > dep[b])
        swap(a, b);
    for(ll i = 18; i >= 0; i--) {
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
    int n, q, u, v;
    cin >> n;
    for(int i = 1; i < n; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    cin >> q;
    while(q--) {
        cin >> u >> v;
        cout << lca(u, v) << "\n";
    }

    return 0;
}
