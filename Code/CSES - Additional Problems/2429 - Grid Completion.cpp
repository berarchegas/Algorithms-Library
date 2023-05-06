// Grid Completion
//
// Problem name: Grid Completion
// Problem Link: https://cses.fi/problemset/task/2429
// Author: Bernardo Archegas (https://codeforces.com/profile/Ber)

#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
 
mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());
    
const int MOD = 1e9 + 7;
const int MAXN = 5e2 + 5;
const ll INF = 2e18;
 
ll fat[MAXN], inv[MAXN];
 
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
    for (ll i = 1; i < MAXN; i++) fat[i] = (i * fat[i - 1]) % MOD;
    inv[MAXN - 1] = fexp(fat[MAXN - 1], MOD - 2);
    for (ll i = MAXN - 2; i >= 0; i--) inv[i] = ((i + 1ll) * inv[i + 1]) % MOD;
}
 
ll nck(int n, int k) {
    if (k > n || k < 0 || n < 0) return 0;
    return (((fat[n] * inv[k]) % MOD) * inv[n - k]) % MOD; 
}
 
void add(int &a, int b) {
    a += b;
    if (a >= MOD) a -= MOD;
    if (a < 0) a += MOD;
}
 
ll mul(ll a, ll b) {
    return (a * b) % MOD;
}
 
int inl[505], inc[505], outl[505], outc[505], v[6], dp[505];
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    precalc();
    int n;
    cin >> n;
    char c;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> c;
            if (c == 'A') {
                outl[i] = j;
                inc[j] = i;
            }
            if (c == 'B') {
                inl[i] = j;
                outc[j] = i;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        v[0] += (!inl[i] && !outl[i]);
        v[1] += (!inc[i] && !outc[i]);
        v[2] += (outl[i] && !outc[outl[i]] && !inl[i]);
        v[3] += (outc[i] && !outl[outc[i]] && !inc[i]);
        v[4] += (!outl[i]);
        v[5] += (!inl[i]);
    }
    for (int i = 0; i <= min(v[0], v[1]); i++) {
        for (int j = 0; j <= v[2]; j++) {
            for (int k = 0; k <= v[3]; k++) {
                ll nv = mul(nck(v[0], i), nck(v[1], i));
                nv = mul(nv, nck(v[2], j));
                nv = mul(nv, nck(v[3], k));
                nv = mul(nv, fat[v[4] - i - k]);
                nv = mul(nv, fat[v[5] - i - j]);
                nv = mul(nv, fat[i]);
                add(dp[i + j + k], nv);
            }
        }
    }
    int ans = 0;
    for (int i = 0; i <= n; i++) {
        add(ans, (i&1 ? MOD - dp[i] : dp[i]));
    }
    cout << ans << '\n';
    return 0;
}