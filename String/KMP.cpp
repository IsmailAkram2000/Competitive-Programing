#include <bits/stdc++.h>
using namespace std;
#define ll long long
 
struct KMP {
    int sz;
    string s;
    vector <int> pi;
 
    void init(string x) {
        s = x;
        sz = s.size();
        pi.resize(sz);
    }
 
    void compute() {
        for(int i = 1; i < sz; i++) {
            int j = pi[i - 1];
            while(j > 0 && s[i] != s[j])
                j = pi[j - 1];
            if(s[i] == s[j])
                j++;
            pi[i] = j;
        }
    }
 
}kmp;
 
int main(){
 
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
 
 
    return 0;
}
