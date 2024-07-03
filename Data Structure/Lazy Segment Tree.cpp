#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct lazy_segment_tree {
    int sz;
    vector<ll> v, lazy;
    vector <bool> to_set;

    void init(int n) {
        sz = 1;
        while (sz < n)
            sz *= 2;
        v.assign(2 * sz, 0);
        lazy.assign(2 * sz, 0);
        to_set.assign(2 * sz, false);
    }

    //  apply if we want the set function to add range
//    void push_down(int cur, int l, int r) {
//        if (lazy[cur]) {
//            v[cur] += lazy[cur] * (r - l + 1); // Update the current node
//            if (l != r) {
//                lazy[2 * cur] += lazy[cur]; // Propagate to left child
//                lazy[2 * cur + 1] += lazy[cur]; // Propagate to right child
//            }
//            lazy[cur] = 0;
//        }
//    }

    //  apply if we want the set function to set range
    void push_down(int cur, int l, int r) {
        if (to_set[cur]) {
            v[cur] = lazy[cur];     // Update the current node
            if (l != r) {
                lazy[2 * cur] = lazy[cur]; // Propagate to left child
                lazy[2 * cur + 1] = lazy[cur]; // Propagate to right child
                to_set[2 * cur] = 1;
                to_set[2 * cur + 1] = 1;
            }
            to_set[cur] = 0;
        }
    }

    void set(int lx, int rx, int val, int cur, int l, int r) {
        push_down(cur, l, r);
        if (lx > r || rx < l) return;
        if (lx <= l && rx >= r) {
//            lazy[cur] += val;
            lazy[cur] = val;
            to_set[cur] = 1;
            push_down(cur, l, r);
            return;
        }
        int mid = (l + r) / 2;
        set(lx, rx, val, 2 * cur, l, mid);
        set(lx, rx, val, 2 * cur + 1, mid + 1, r);
        v[cur] = max(v[2 * cur], v[2 * cur + 1]);
    }

    ll query(int lx, int rx, int cur, int l, int r) {
        push_down(cur, l, r);
        if (lx > r || rx < l) return -1;
        if (lx <= l && rx >= r) return v[cur];
        int mid = (l + r) / 2;
        ll left = query(lx, rx, 2 * cur, l, mid);
        ll right = query(lx, rx, 2 * cur + 1, mid + 1, r);
        return max(left, right);
    }

    void set(int l, int r, int val) {
        if (l > r) swap(l, r);
        set(l, r, val, 1, 1, sz);
    }

    ll query(int l, int r) {
        if (l > r) swap(l, r);
        return query(l, r, 1, 1, sz);
    }
}seg;

int main() {

    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);


    return 0;
}
