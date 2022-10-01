// Coin Arrangement
//
// Problem name: Coin Arrangement
// Problem Link: https://cses.fi/problemset/task/2180
// Author: Bernardo Archegas (https://codeforces.com/profile/Ber)

// There is a 2 x n grid whose each cell contains some number of coins. The total number of coins is 2n.
// Your task is to arrange the coins so that each cell contains exactly one coin. 
// On each move you can choose any coin and move it one step left, right, up or down.
// What is the minimum number of moves if you act optimally?

#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
 
mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());
 
const int MOD = 1e9 + 7;
const int MAXN = 1e5 + 5;
const ll INF = 1e18;
 
int v1[MAXN], v2[MAXN];
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) 
        cin >> v1[i], v1[i]--;
    for (int i = 0; i < n; i++) 
        cin >> v2[i], v2[i]--;
    int cima = 0, baixo = 0;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ans += abs(cima) + abs(baixo);
        cima += v1[i];
        baixo += v2[i];
        while (cima > 0 && baixo < 0) 
            cima--, baixo++, ans++;
        while (cima < 0 && baixo > 0)
            cima++, baixo--, ans++;
    }
    cout << ans << '\n';
    return 0;
}