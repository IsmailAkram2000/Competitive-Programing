#include<bits/stdc++.h>
using namespace std;
#define ll long long

const int K = 26;

struct node {
    int next[K];
    bool is_leaf;

    node() {
        memset(next, -1, sizeof(next));
        is_leaf = false;
    }
};

struct aho_corasick {
    vector <node> trie;

    aho_corasick() {
        trie.resize(1);
    }

    void insert(string s) {
        int cur = 0;
        for(auto c: s) {
            int i = c - 'a';
            if(trie[cur].next[i] == -1) {
                trie[cur].next[i] = trie.size();
                trie.emplace_back();
            }
            cur = trie[cur].next[i];
        }
        trie[cur].is_leaf = true;
    }

    bool Find(string s) {
        int cur = 0;
        for(auto c: s) {
            int i = c - 'a';
            if(trie[cur].next[i] == -1)
                return false;
            cur = trie[cur].next[i];
        }
        return trie[cur].is_leaf;
    }

    bool Find_prefix(string s) {
        int cur = 0;
        for(auto c: s) {
            int i = c - 'a';
            if(trie[cur].next[i] == -1)
                return false;
            cur = trie[cur].next[i];
        }
        return true;
    }

}aho;

int main(){

    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);


    return 0;
}
