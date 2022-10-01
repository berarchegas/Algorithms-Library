// Centroid: Query de distancia
//
// Query: Dado v e x, quantos vertices u tem tal que d(v, u) <= x?

#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
 
mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());
    
const int MOD = 1e9 + 7;
const int MAXN = 1e5 + 5;
const ll INF = 2e18;
 
vector<pii> v[MAXN];
vector<ll> arv[MAXN], arv2[MAXN];
int sz[MAXN], pai[MAXN], lvl[MAXN], n, q;
bool vis[MAXN];
ll d[20][MAXN];


// centroid decomposition
int subtree(int node, int p = 0) {
    sz[node] = 1;
    for (pii x : v[node]) {
        if (!vis[x.first] && x.first != p) {
            sz[node] += subtree(x.first, node);
        }
    }
    return sz[node];
}
int centroid(int node, int desired, int p = 0) {
    for (pii x : v[node]) {
        if (!vis[x.first] && x.first != p && sz[x.first] > desired) {
            return centroid(x.first, desired, node);
        }
    }
    return node;
}
void dfs(int node, int p, int l, ll dist, int root) {
    d[l][node] = dist;
    for (pii x : v[node]) {
        if (!vis[x.first] && x.first != p) {
            dfs(x.first, node, l, dist + x.second, root);
        }
    }
}
void solve(int node, int p = 0) {
    int c = centroid(node, subtree(node) / 2);
    vis[c] = true;
    if (p == 0) {
        pai[c] = c;
        lvl[c] = 0;
    }
    else {
        pai[c] = p;
        lvl[c] = lvl[p] + 1;
    }
    dfs(c, p, lvl[c], 0, c);
    for (pii x : v[c]) {
        if (!vis[x.first]) {
            solve(x.first, c);
        }
    }
}
void build_arv() {
	for (int i = 1; i <= n; i++) {
		int u = i;
		while(1) {
			arv[u].push_back(d[lvl[u]][i]);
			if(u == pai[u])break;
			u = pai[u];
		}
	}
	for(int i = 1; i <= n; i++)
		sort(arv[i].begin(), arv[i].end());
}
void build_arv2() {
    for (int i = 1; i <= n; i++) {
		int u = i;
		while(1) {
			arv2[u].push_back(d[lvl[pai[u]]][i]);
			if(u == pai[u])break;
			u = pai[u];
		}
	}
	for(int i = 1; i <= n; i++)
		sort(arv2[i].begin(), arv2[i].end());
}
 
 
// queries
int query(int node, ll dist) {
    int ans = 0, x = node;
    ans += (upper_bound(arv[x].begin(), arv[x].end(), dist) - arv[x].begin());
    while (true) {
        if (x == pai[x]) break;
        ans += (upper_bound(arv[pai[x]].begin(), arv[pai[x]].end(), dist - d[lvl[pai[x]]][node]) - arv[pai[x]].begin());
        ans -= (upper_bound(arv2[x].begin(), arv2[x].end(), dist - d[lvl[pai[x]]][node]) - arv2[x].begin());
        x = pai[x];
    }
    return ans;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> q;
    int a, b, c;
    for (int i = 0; i < n - 1; i++) {
        cin >> a >> b >> c;
        v[a].emplace_back(b, c);
        v[b].emplace_back(a, c);
    }
    solve(1);
    build_arv();
    build_arv2();
    ll v, l;
    while (q--) {
        cin >> v >> l;
        cout << query(v, l) << '\n';
    }
    return 0;
}