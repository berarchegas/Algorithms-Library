#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
 
mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());
    
const int MOD = 1e9 + 7;
const int MAXN = 2e5 + 5;
const ll INF = 1e18;

vector<array<int, 3>> v;
ll dist[MAXN];
int p[MAXN];
 
int main() { 
	ios::sync_with_stdio(false);
    cin.tie(0);
	int n, m;
	cin >> n >> m;
	array<int, 3> a;

	// recebe aresta de a pra b com custo c
	for (int i = 0; i < m; i++) {
		cin >> a[0] >> a[1] >> a[2];
		v.push_back(a);
	}
	int x = -1;
	for (int i = 2; i <= n; i++) dist[i] = INF;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (dist[v[j][0]] + v[j][2] < dist[v[j][1]]) {
				dist[v[j][1]] = dist[v[j][0]] + v[j][2];
				p[v[j][1]] = v[j][0];
				if (i == n-1) x = v[j][1];
			}
		}
	}
	if (x == -1) cout << "NO\n";
	else {
		cout << "YES\n";
		for (int i = 0; i < n; i++) x = p[x];
		stack<int> ans;
		ans.push(x);
		for (int i = p[x]; i != x; i = p[i]) {
			ans.push(i);
		}
		ans.push(x);
		while (!ans.empty()) {
			cout << ans.top() << ' ';
			ans.pop();
		}
		cout << '\n';
	}
    return 0;
}