// Comb Template
//
// template para problemas de combinatoria
int fat[MAXN], inv[MAXN];

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