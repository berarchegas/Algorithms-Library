// Houses and Schools
//
// Problem name: Houses and Schools
// Problem Link: https://cses.fi/problemset/task/2087
// Author: Bernardo Archegas (https://codeforces.com/profile/Ber)

// There are n houses on a street, numbered 1,2,…,n. The distance of houses a and b is |a−b|. 
// You know the number of children in each house.
// Your task is to establish k schools in such a way that each school is in some house. 
// Then, each child goes to the nearest school. 
// What is the minimum total walking distance of the children if you act optimally?

#include <bits/stdc++.h>
    
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
    
mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());
    
const int MOD = 1e9 + 7;
const int MAXN = 3e3 + 5;
const int INF = 2e9;
 
ll c[MAXN][MAXN], dp[MAXN][MAXN], v[MAXN], pre[MAXN];
 
void solve(int l, int r, int ini, int fim, int k) {
    int m = (l + r) / 2;
    ll dude = 0, mn = 1e18;
    for (int i = ini; i <= min(m - 1, fim); i++) {
        if (dp[k - 1][i] + c[i][m] < mn) {
            dude = i;
            mn = dp[k - 1][i] + c[i][m];
        }
    }
    dp[k][m] = mn;
    if (m - 1 >= l)
        solve(l, m - 1, ini, dude, k);
    if (r >= m + 1)
        solve(m + 1, r, dude, fim, k);
}
 
int main () {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
        pre[i] = v[i] + pre[i - 1];
    }
 
    // calc custo normal
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            c[i][j] = c[i][j - 1] + pre[j - 1] - pre[(i + j - 1) / 2];
        }
    }
 
    // calc custo das bordas
    for (int i = 2; i <= n; i++) {
        c[0][i] = c[0][i - 1] + pre[i - 1];
    }
    for (int i = n - 1; i >= 1; i--) {
        c[i][n + 1] = c[i + 1][n + 1] + pre[n] - pre[i];
    }
    for (int i = 0; i <= n + 1; i++) {
        for (int j = 0; j <= n + 1; j++) dp[i][j] = 1e18;
    }
    dp[0][0] = 0;
    for (int i = 1; i <= k + 1; i++) 
        solve(1, n + 1, 0, n, i);
    cout << dp[k + 1][n + 1] << '\n';
    return 0;
}