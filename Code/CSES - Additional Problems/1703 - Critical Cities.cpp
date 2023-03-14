// Critical Cities
//
// Problem name: Critical Cities
// Problem Link: https://cses.fi/problemset/task/1703
// Author: Bernardo Archegas (https://codeforces.com/profile/Ber)

// There are n cities and m flight connections between them. 
// A city is called a critical city if it appears on every route from a city to another city.
// Your task is to find all critical cities from 1 to n

#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
 
mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());
    
const int MOD = 1e9 + 7;
const int MAXN = 2e5 + 5;
const ll INF = 2e18;
 
// Dominator Tree - Kawakami
//
// Se vira pra usar ai
//
// build - O(n)
// dominates - O(1)
// c80920
 
int n;
 
namespace d_tree {
	vector<int> g[MAXN];
 
	// The dominator tree
	vector<int> tree[MAXN];
	int dfs_l[MAXN], dfs_r[MAXN];
 
	// Auxiliary data
	vector<int> rg[MAXN], bucket[MAXN];
	int idom[MAXN], sdom[MAXN], prv[MAXN], pre[MAXN];
	int ancestor[MAXN], label[MAXN];
	vector<int> preorder;
 
	void dfs(int v) {
		static int t = 0;
		pre[v] = ++t;
		sdom[v] = label[v] = v;
		preorder.push_back(v);
		for (int nxt: g[v]) {
			if (sdom[nxt] == -1) {
				prv[nxt] = v;
				dfs(nxt);
			}
			rg[nxt].push_back(v);
		}
	}
	int eval(int v) {
		if (ancestor[v] == -1) return v;
		if (ancestor[ancestor[v]] == -1) return label[v];
		int u = eval(ancestor[v]);
		if (pre[sdom[u]] < pre[sdom[label[v]]]) label[v] = u;
		ancestor[v] = ancestor[u];
		return label[v];
	}
	void dfs2(int v) {
		static int t = 0;
		dfs_l[v] = t++;
		for (int nxt: tree[v]) dfs2(nxt);
		dfs_r[v] = t++;
	}
	void build(int s) {
		for (int i = 0; i < n; i++) {
			sdom[i] = pre[i] = ancestor[i] = -1;
			rg[i].clear();
			tree[i].clear();
			bucket[i].clear();
		}
		preorder.clear();
		dfs(s);
		if (preorder.size() == 1) return;
		for (int i = int(preorder.size()) - 1; i >= 1; i--) {
			int w = preorder[i];
			for (int v: rg[w]) {
				int u = eval(v);
				if (pre[sdom[u]] < pre[sdom[w]]) sdom[w] = sdom[u];
			}
			bucket[sdom[w]].push_back(w);
			ancestor[w] = prv[w];
			for (int v: bucket[prv[w]]) {
				int u = eval(v);
				idom[v] = (u == v) ? sdom[v] : u;
			}
			bucket[prv[w]].clear();
		}
		for (int i = 1; i < preorder.size(); i++) {
			int w = preorder[i];
			if (idom[w] != sdom[w]) idom[w] = idom[idom[w]];
			tree[idom[w]].push_back(w);
		}
		idom[s] = sdom[s] = -1;
		dfs2(s);
	}
 
	// Whether every path from s to v passes through u
	bool dominates(int u, int v) {
		if (pre[v] == -1) return 1; // vacuously true
		return dfs_l[u] <= dfs_l[v] && dfs_r[v] <= dfs_r[u];
	}
};
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int m, a, b;
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		a--, b--;
		d_tree::g[a].push_back(b);
	}
	d_tree::build(0);
	vector<int> ans;
	for (int i = 0; i < n; i++) {
		if (d_tree::dominates(i, n - 1)) ans.push_back(i + 1);
	}
	cout << ans.size() << '\n';
	for (int x : ans) cout << x << ' ';
	cout << '\n';
    return 0;
}