#include <bits/stdc++.h>
using namespace std;
#define ll long long
 
struct suffix_hash {
    int n;
    string s;
    vector<ll> pow1, pow2, h1, h2;
    const int p1 = 313, p2 = 1013;
    const int m1 = 1e9 + 7, m2 = 1e9 + 9;
 
    void init(string x) {
        s = x;
        n = s.size();
        h1.resize(n);
        h2.resize(n);
        pow1.resize(n);
        pow2.resize(n);
        compute();
    }
 
    void compute() {
        pow1[0] = pow2[0] = 1;
        for(int i = 1; i < n; i++) {
            pow1[i] = (pow1[i - 1] * p1) % m1;
            pow2[i] = (pow2[i - 1] * p2) % m2;
        }
        h1[0] = h2[0] = s[0];
        for(int i = 1; i < n; i++) {
            h1[i] = (h1[i - 1] * p1 + s[i]) % m1;
            h2[i] = (h2[i - 1] * p2 + s[i]) % m2;
        }
    }
 
    pair <ll, ll> get_hash(int i, int j) {
        ll a = h1[j];
        if(i)
            a -= h1[i - 1] * pow1[j - i + 1];
        a = ((a % m1) + m1) % m1;
        ll b = h2[j];
        if(i)
            b -= h2[i - 1] * pow2[j - i + 1];
        b = ((b % m2) + m2) % m2;
        return {a, b};
    }
 
    pair <ll, ll> merge_hash(int i, int j, int k, int l) {
        auto a = get_hash(i, j), b = get_hash(k, l);
        return {((a.first * pow1[l - k + 1]) + b.first) % m1,
                ((a.second * pow2[l - k + 1]) + b.second) % m2};
    }
 
}h;
 
int main(){
 
 	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
 	
 
    return 0;
}
