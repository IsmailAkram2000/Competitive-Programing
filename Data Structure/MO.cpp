#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int N = 100010;
const int SQ = sqrt(N);
int lx = 1, rx = 0, cur_res = 0;
vector <int> res(N);

struct query {
	int l, r, k, idx;

	bool operator<(const query& RHS) const{
		int sign = (l / SQ) & 1 ? -1 : 1;
		return make_pair(l/SQ, sign * r) < make_pair(RHS.l / SQ, sign * RHS.r);
	}
};

void add(int idx){

}

void remove(int idx){

}

void solve(query q){
	while(rx < q.r)
		add(++rx);
	while(lx > q.l)
		add(--lx);
	while(rx > q.r)
		remove(rx--);
	while(lx < q.l)
		remove(lx++);
	res[q.idx] = cur_res;
}

int main() {

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);


    return 0;
}
