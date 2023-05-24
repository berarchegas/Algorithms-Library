// School Excursion
//
// Problem name: School Excursion
// Problem Link: https://cses.fi/problemset/task/1706
// Author: Bernardo Archegas (https://codeforces.com/profile/Ber)

// A group of n children are coming to Helsinki. 
// There are two possible attractions: a child can visit either Korkeasaari (zoo) or Linnanmaki (amusement park).
// There are m pairs of children who want to visit the same attraction. 
// Your task is to find all possible alternatives for the number of children that will visit Korkeasaari. 
// The children's wishes have to be taken into account.
// Knapsack em Nsqrt(n)/32

#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
 
mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());
    
const int MOD = 1e9 + 7;
const int MAXN = 2e5 + 5;
const ll INF = 2e18;
 
const ll base = 1e12;
 
vector<int> v[MAXN], vals;
int vis[MAXN], cnt, dp[MAXN], used[MAXN], have[MAXN];
 
void dfs(int node) {
	cnt++;
	vis[node] = 1;
	for (int x : v[node]) 
		if (!vis[x]) dfs(x);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m, a, b;
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		v[a].push_back(b);
		v[b].push_back(a);
	}
	for (int i = 1; i <= n; i++) {
		if (!vis[i]) {
			cnt = 0;
			dfs(i);
			vals.push_back(cnt);
		}
	}
	for (int x : vals) have[x]++;
    bitset<200010> dp;
    dp[0] = 1;
    for (int i = 1; i < 100005; i++) {
        while (have[i] > 2) {
            have[i] -= 2;
            have[2 * i]++;
        }
        while (have[i]--) {
            dp |= (dp << i);
        }
    }
    
    for (int i = 1; i <= n; i++) cout << dp[i];
    cout << '\n';
    return 0;
}