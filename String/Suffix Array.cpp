#include <bits/stdc++.h>
using namespace std;
#define ll long long
 
struct suffix_array {
 
	string x; 
	int n;
	vector <int> suffix, c, lcp;
 
public:
 
	void init(string s = "") {
		x = s;
		n = x.size();
		c.resize(n);
		lcp.resize(n);
		suffix.resize(n);
	}
 
	void count_sort(vector <int> &p) {
		vector <int> cnt(n);
		for(auto a: c)
		  	cnt[a]++;
		vector <int> p_new(n), pos(n);
		pos[0] = 0;
		for(int i = 1; i < n; i++)
			pos[i] = pos[i - 1] + cnt[i - 1];
		for(auto a: p){
			int i = c[a];
			p_new[pos[i]] = a;
			pos[i]++;
		}
		p = p_new;
	}
 
	void build_suffix() {
		vector < pair <char, int > > v(n);
		for(int i = 0; i < n; i++)
				v[i] = {x[i], i};
		sort(v.begin(), v.end());
		for(int i = 0; i < n; i++)
			suffix[i] = v[i].second;
		c[suffix[0]] = 0;
		for(int i = 1; i < n; i++)
			c[suffix[i]] = c[suffix[i - 1]] + (v[i].first != v[i - 1].first);
		int k = 0;
		while((1 << k) < n){
			for(int i = 0; i < n; i++)
				suffix[i] = (suffix[i] - (1 << k) + n ) % n;
			count_sort(suffix);
			c[suffix[0]] = 0;
			vector <int> c_new(n);
			c_new[suffix[0]] = 0;
			for(int i = 1; i < n; i++) {
				pair <int, int> prev = {c[suffix[i - 1]], c[(suffix[i - 1] + (1 << k)) % n]};
				pair <int, int> cur = {c[suffix[i]], c[(suffix[i] + (1 << k)) % n]};
				c_new[suffix[i]] = c_new[suffix[i - 1]] + (prev != cur);
			}
			c = c_new;
			k++;
		}
	}
 
	int lower_bound(string y) {
		int l = 0, r = n - 1, res = -1;
		while(l <= r) {
			int mid = (l + r) / 2, st = suffix[mid], sz = y.size();
			string suf = x.substr(st, min(sz, n - st + 1));
			if(suf == y)
				res = mid;
			if(suf < y)
				l = mid + 1;
			else
				r = mid - 1;
		}		
		return res;
	}
 
	int upper_bound(string y) {
		int l = 0, r = n - 1, res = -1;
		while(l <= r) {
			int mid = (l + r) / 2, st = suffix[mid], sz = y.size();
			string suf = x.substr(st, min(sz, n - st + 1));
			if(suf == y)
				res = mid;
			if(suf <= y) 
				l = mid + 1;
			else
				r = mid - 1;
		}		
		return res;		
	}
 
	void build_lcp() {
		int k = 0;
		for(int i = 0; i < n - 1; i++) {
			int pi = c[i], j = suffix[pi - 1];
			while(x[i + k] == x[j + k]) {
				k++;
			}
			lcp[pi] = k;
			k = max(k - 1, 0);
		}
	}
 
	ll number_of_diff_substring() {
		ll sum = 0;
		for(int i = 0; i < n; i++)
			sum += (n - (1 + lcp[i] + suffix[i])); 
		return sum;
	}
 
	string Lcs(string s1, string s2) {
		init(s1 + '$' + s2 + '#');
		build_suffix();
		build_lcp();
		vector <int> lvl(n);
		int mx = 0;
		for (int i = 0; i < n; i++) {
			(suffix[i] < int(s1.size())) ? lvl[i] = 1 : lvl[i] = 2;
			if(lvl[i] != lvl[max(0, i - 1)]) 				
				mx = max(mx, lcp[i]);
		}
		if(mx == 0)
			return "";
		for(int i = 1; i < n; i++) {
			if(lvl[i] != lvl[i - 1] && lcp[i] == mx)
				return x.substr(suffix[i], lcp[i]);
		} 
		return "";
	}
 
	void print() {
		for(int i = 0; i < n; i++)
			cout << suffix[i] << " ";
		cout << "\n";
		for(int i = 1; i < n; i++)
			cout << lcp[i] << " ";
	}
 
}sa;
 
int main(){
 
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
 
 
	return 0;
}
