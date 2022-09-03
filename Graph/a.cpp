#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
 
mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());
    
const int MOD = 1e9 + 7;
const int MAXN = 2e5 + 5;
const ll INF = 2e18;

vector<int> v[MAXN];
int n;
 
int bfs(int node, bool flag) {
    // flag = true se estou fazendo a segunda BFS
	
    queue<pii> q;
	vector<int> check(n+1);
	check[node] = 1;
	q.push({node, 0});
	int resp = 0, fim = node;
	while (!q.empty()) {
		pii atual = q.front();
		q.pop();
		for (int x : v[atual.first]) {
			if (!check[x]) {
				check[x] = 1;
				q.push({x, atual.second+1});
				if (atual.second + 1 > resp) {
					resp = atual.second + 1;
					fim = x;
				}
			}
		}
	}
	return (flag ? resp : fim);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int a, b;
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		cin >> a >> b;
		v[a].push_back(b);
		v[b].push_back(a);
	}
	a = bfs(1, 0);
	cout << bfs(a, 1) << '\n';
    return 0;
}