#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
 
mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());
    
const int MOD = 1e9 + 7;
const int MAXN = 2e5 + 5;
const ll INF = 2e18;

vector<int> v[MAXN], ans;
bool valid = true;
int cor[MAXN];
 
void dfs(int node) {
	cor[node] = 1;
	for (int x : v[node]) {
		if (cor[x] == 1) {
			valid = false;
			return;
		}
		if (!cor[x]) dfs(x);
	}
	cor[node] = 2;
	ans.push_back(node);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		v[a].push_back(b);
	}
	for (int i = 1; i <= n && valid; i++) {
		if (!cor[i]) {
			dfs(i);
		}
	}
	if (!valid) cout << "IMPOSSIBLE\n";
	else {
		reverse(ans.begin(), ans.end());
		for (int x : ans) cout << x << ' ';
		cout << '\n';
	}
    return 0;
}