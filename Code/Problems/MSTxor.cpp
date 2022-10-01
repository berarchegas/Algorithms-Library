// MST-XOR
// 
// You are given a complete undirected graph with n vertices. 
// A number ai is assigned to each vertex, and the weight of an edge between vertices i and j is equal to ai xor aj.
// Calculate the weight of the minimum spanning tree in this graph.

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());
    
const int MOD = 1e9 + 7;
const int MAXN = 2e5 + 5;
const ll INF = 2e18;

int at = 0, trie[(int)6e6 + 5][2], qtd[(int)6e6 + 5];
int p[MAXN], sz[MAXN];
pii mn[MAXN]; 
vector<int> cmp[MAXN];
set<int> comps, apaga;
map<int, int> mp;

int find(int x) { return p[x] = (x == p[x] ? x : find(p[x])); }

void join(int a, int b) {
    a = find(a), b = find(b);
    if (sz[a] < sz[b]) swap(a, b);
    for (int x : cmp[b]) {
        cmp[a].push_back(x);
    }
    p[b] = a;
    sz[a] += sz[b];
    apaga.insert(b);
    cmp[b].clear();
}

void insert(int x, int add) {
    int node = 0;
    for (int i = 29; i >= 0; i--) {
        int &a = trie[node][!!(x & (1 << i))];
        if (!a) {
            a = ++at;
        }
        node = a;
        qtd[node] += add;
    }
}

pii mini(int x) {
    int node = 0, ans = 0, val = 0;
    for (int i = 29; i >= 0; i--) {
        if (trie[node][!!(x & (1 << i))] && qtd[trie[node][!!(x & (1 << i))]]) {
            node = trie[node][!!(x & (1 << i))];
            val += (x & (1 << i));
        }
        else {
            node = trie[node][!(x & (1 << i))];
            val += ((x & (1 << i)) ? 0 : (1 << i));
            ans += (1 << i);
        }
    }
    return {ans, find(mp[val])};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, aux;
    ll ans = 0;
    cin >> n;
    set<int> st;
    for (int i = 0; i < n; i++) {
        cin >> aux;
        st.insert(aux);
    }
    n = st.size();
    int cnt = 0;
    for (int x : st) {
        mp[x] = cnt;
        comps.insert(cnt);
        insert(x, 1);
        cmp[cnt].push_back(x);
        p[cnt] = cnt;
        sz[cnt] = 1;
        cnt++;
    }
    int qtd = n;
    while (qtd > 1) {
        for (int i : comps) {
            mn[i] = {(1 << 30), 0};
            for (int x : cmp[i]) {
                insert(x, -1);
            }
            for (int x : cmp[i]) {
                mn[i] = min(mn[i], mini(x));
            }
            for (int x : cmp[i]) {
                insert(x, 1);
            }
        }
        int nqtd = qtd;
        for (int i : comps) {
            if (find(mn[i].second) != find(i)) {
                // join
                nqtd--;
                ans += mn[i].first;
                join(mn[i].second, i);
            }
        }
        for (int x : apaga) comps.erase(x);
        apaga.clear();
        qtd = nqtd;
    }
    cout << ans << '\n';
    return 0;
};