// Parallel Binary Search
//
// M da Subregional 2022 - Hopscotch Marathon

#include <bits/stdc++.h>
    
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
    
mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());
    
const int MOD = 1e9 + 7;
const int MAXN = 1e5 + 5;
const int INF = 2e9;

int a[MAXN], cmp[MAXN], ans[MAXN];
ll primes[MAXN];
pii v[MAXN];

void add(int id, ll mul) {
    int c = v[id].first, d = v[id].second;
    vector<int> primos;
    while (c != 1) {
        primos.push_back(cmp[c]);
        c /= cmp[c];
    }
    sort(primos.begin(), primos.end());
    primos.erase(unique(primos.begin(), primos.end()), primos.end());
    int tam = primos.size();
    for (int msk = 1; msk < (1 << tam); msk++) {
        int num = 1;
        for (int j = 0; j < tam; j++) {
            if (msk & (1 << j)) num *= primos[j];
        }
        if (__builtin_popcount(msk) & 1) {
            primes[num] += mul * d;
        }
        else {
            primes[num] -= mul * d;
        }
    }
}

ll get_walk(int c) {
    vector<int> primos;
    while (c != 1) {
        primos.push_back(cmp[c]);
        c /= cmp[c];
    }
    sort(primos.begin(), primos.end());
    primos.erase(unique(primos.begin(), primos.end()), primos.end());
    int tam = primos.size();
    ll ans = 0;
    for (int msk = 1; msk < (1 << tam); msk++) {
        int num = 1;
        for (int j = 0; j < tam; j++) {
            if (msk & (1 << j)) num *= primos[j];
        }
        ans += primes[num];
    }
    return ans;
}

void parallel_binary_search(int l, int r, vector<int> &candidates) {
    
    if (candidates.empty()) return;
    if (l == r) {
        for (int x : candidates) {
            ans[x] = r;
        }
        return;
    }
    int m = (l + r) / 2;
    for (int i = l; i <= m; i++) add(i, 1);
    vector<int> ok, nok;

    for (int x : candidates) {
        if (get_walk(x) >= a[x]) ok.push_back(x);
        else nok.push_back(x);
    }
    candidates.clear();
    parallel_binary_search(m + 1, r, nok);
    for (int i = l; i <= m; i++) add(i, -1);
    parallel_binary_search(l, m, ok);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    for (int i = 2; i < MAXN; i++) {
        if (!cmp[i]) {
            for (int j = i; j < MAXN; j += i) cmp[j] = i;
        }
    }
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 0; i < q; i++) cin >> v[i].first >> v[i].second;
    vector<int> candidates;
    for (int i = 1; i <= n; i++) candidates.push_back(i);
    parallel_binary_search(0, q, candidates);
    for (int i = 1; i <= n; i++) cout << (ans[i] == q ? -1 : ans[i] + 1) << '\n';
    return 0;
}