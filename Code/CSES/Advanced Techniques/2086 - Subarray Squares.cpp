// Subarray Squares
//
// Problem name: Subarray Squares
// Problem Link: https://cses.fi/problemset/task/2086
// Author: Bernardo Archegas (https://codeforces.com/profile/Ber)

// Given an array of n elements, your task is to divide into k subarrays. 
// The cost of each subarray is the square of the sum of the values in the subarray. 
// What is the minimum total cost if you act optimally?

#include <bits/stdc++.h>
    
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
    
mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());
    
const int MOD = 1e9 + 7;
const int MAXN = 3e3 + 5;
const int INF = 2e9;
 
ll dp[MAXN][MAXN], v[MAXN];
 
ll c(int a, int b) { return (v[b] - v[a - 1]) * (v[b] - v[a - 1]);}
 
void solve(int l, int r, int ini, int fim, int k) {
    int m = (l + r) / 2;
    ll dude = -1, mn = 1e18;
    for (int i = ini; i <= min(m - 1, fim); i++) {
        if (dp[k - 1][i] + c(i + 1, m) < mn) {
            dude = i;
            mn = dp[k - 1][i] + c(i + 1, m);
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
        v[i] += v[i - 1];
    }
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) dp[i][j] = 1e18;
    }
    dp[0][0] = 0;
    for (int i = 1; i <= k; i++) 
        solve(1, n, 0, n, i);
    cout << dp[k][n] << '\n';
    return 0;
}