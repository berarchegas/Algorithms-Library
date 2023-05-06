// Eulerian Subgraphs
//
// Problem name: Eulerian Subgraphs
// Problem Link: https://cses.fi/problemset/task/2078
// Author: Bernardo Archegas (https://codeforces.com/profile/Ber)

// You are given an undirected graph that has n nodes and m edges.
// We consider subgraphs that have all nodes of the original graph and some of its edges. 
// A subgraph is called Eulerian if each node has even degree.
// Your task is to count the number of Eulerian subgraphs modulo 10 ^9+7.

#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define MAXN 200100
#define INF 1e18
#define pb push_back
#define F first
#define S second
 
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int M = 1e9+7;
 
int fexp(ll b, int e) {
	if (e < 0) return 1;
	ll resp = 1;
	while (e) {
		if (e&1) resp = (resp * b) % M;
		b = (b * b) % M;
		e >>= 1;
	}
	return resp;
}
 
vector<int> v[MAXN];
int vis[MAXN];
 
void dfs(int node) {
	vis[node] = 1;
	for (int x : v[node]) {
		if (!vis[x]) dfs(x);
	}
}
 
int main() { _
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		v[a].pb(b);
		v[b].pb(a);
	}
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		if (!vis[i]) {
			cnt++;
			dfs(i);
		}
	}
	cout << fexp(2, m - n + cnt) << '\n';
	return 0;
}