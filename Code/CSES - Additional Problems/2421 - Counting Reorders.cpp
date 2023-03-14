// Counting Reorders
//
// Problem name: Counting Reorders
// Problem Link: https://cses.fi/problemset/task/2421
// Author: Bernardo Archegas (https://codeforces.com/profile/Ber)

// Calculate the number of ways you can reorder the characters 
// of a string so that no two adjacent characters are the same.
// For example, the answer for aabc is 6, 
// because the possible orders are abac, abca, acab, acba, baca, and caba.

#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
 
mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());
    
const int MOD = 1e9 + 7;
const int MAXN = 5e3 + 5;
const ll INF = 2e18;
 
int fat[MAXN], inv[MAXN], dp1[MAXN], dp2[MAXN], qtd[26];
 
ll fexp(ll b, ll e) {
    ll ans = 1;
    while (e) {
        if (e&1) ans = (ans * b) % MOD;
        b = (b * b) % MOD;
        e >>= 1;
    }
    return ans;
}
 
void precalc() {
    fat[0] = 1;
    for (int i = 1; i < MAXN; i++) fat[i] = (1ll * i * fat[i - 1]) % MOD;
    inv[MAXN - 1] = fexp(fat[MAXN - 1], MOD - 2);
    for (int i = MAXN - 2; i >= 0; i--) inv[i] = ((i + 1ll) * inv[i + 1]) % MOD;
}
 
int nck(int n, int k) {
    if (k > n || k < 0 || n < 0) return 0;
    return (((1ll * fat[n] * inv[k]) % MOD) * 1ll * inv[n - k]) % MOD; 
}
 
void add(int &a, int b) {
    a += b;
    if (a >= MOD) a -= MOD;
    if (a < 0) a += MOD;
}
 
int mul(int a, int b) {
    return (1ll * a * b) % MOD;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    precalc();
    string s;
    cin >> s;
    int n = s.size(), tot = 0;
    for (auto x : s) qtd[x - 'a']++;
    dp1[0] = 1;
    for (int i = 0; i < 26; i++) {
        // char atual
 
        if (!qtd[i]) continue;
        for (int j = 0; j <= tot; j++) {
            // qtd de grupos q eu tenho
 
            for (int k = 1; k <= qtd[i]; k++) {
                // qtd de grupos q vou add
 
                add(dp2[j + k], mul(dp1[j], mul(nck(qtd[i] - 1, k - 1), nck(j + k, k))));
            }
        }
        tot += qtd[i];
        for (int j = 0; j <= tot; j++) {
            dp1[j] = dp2[j];
            dp2[j] = 0;
        }
    }
    int ans = 0;
    for (int i = n; i > 0; i--) {
        if ((n - i) & 1) add(ans, MOD - dp1[i]);
        else add(ans, dp1[i]);
    }
    cout << ans << '\n';
    return 0;
}