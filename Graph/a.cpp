#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
 
mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());
    
const int MOD = 1e9 + 7;
const int MAXN = 2e5 + 5;
const ll INF = 2e18;

const int MAXL = 20;
int dep[MAXN], tab[MAXL][MAXN];
vector<int> v[MAXN];

void dfs(int node, int pai = 0) {
    dep[node] = dep[pai] + 1;
    tab[0][node] = pai;
    for (int x : v[node]) {
        if (x != pai) dfs(x, node);
    }
}

void calcTab(int n) {
    for (int i = 1; i < MAXL; i++) {
        for (int j = 1; j <= n; j++) tab[i][j] = tab[i - 1][tab[i - 1][j]]; 
    }
}

int lca(int a, int b) {
    if (dep[a] < dep[b]) swap(a, b);
    for (int i = MAXL - 1; i >= 0; i--) {
        if (dep[a] - (1 << i) >= dep[b]) {
            a = tab[i][a];
        }
    }
    if (a == b) return a;
    for (int i = MAXL - 1; i >= 0; i--) {
        if (tab[i][a] != tab[i][b]) {
            a = tab[i][a];
            b = tab[i][b];
        }
    }
    return tab[0][a];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
	cin >> n >> q;
	for (int i = 2; i <= n; i++) {
		cin >> tab[0][i];
		v[i].push_back(tab[0][i]);
		v[tab[0][i]].push_back(i);
	}
	dfs(1);
	calcTab(n);
	int a, b;
	for (int i = 0; i < q; i++) {
		cin >> a >> b;
		cout << lca(a, b) << '\n';
	}
    return 0;
}