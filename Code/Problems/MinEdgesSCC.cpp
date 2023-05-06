#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
 
mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());
    
const int MOD = 1e9 + 7;
const int MAXN = 1e5 + 5;
const ll INF = 2e18;

int rep[MAXN], vis[MAXN], cmp[MAXN], cnt;
vector<int> v[MAXN], w[MAXN], nv[MAXN], nw[MAXN], src, snk, ord;

void dfs1(int node) {
    vis[node] = 1;
    for (int x : v[node]) {
        if (!vis[x]) dfs1(x);
    }
    ord.push_back(node);
}

void dfs2(int node) {
    vis[node] = 1;
    cmp[node] = cnt;
    rep[cnt] = node;
    for (int x : w[node]) {
        if (!vis[x]) dfs2(x);
    }
}

void dfs3(int node) {
    vis[node] = 1;
    if (nv[node].empty()) snk.push_back(node);
    if (nw[node].empty()) src.push_back(node);
    for (int x : nv[node]) {
        if (!vis[x]) dfs3(x);
    }
    for (int x : nw[node]) {
        if (!vis[x]) dfs3(x);
    }
}

int dfs4(int node) {
    int ans = -1;
    vis[node] = 1;
    if (nv[node].empty()) return node;
    for (int x : nv[node]) {
        if (!vis[x]) {
            ans = dfs4(x);
            if (ans != -1) return ans;
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m, a, b;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        v[a].push_back(b);
        w[b].push_back(a);
    }
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) dfs1(i);
    }
    memset(vis, 0, sizeof(vis));
    reverse(ord.begin(), ord.end());
    for (int x : ord) {
        if (!vis[x]) {
            dfs2(x);
            cnt++;
        }
    }
    if (cnt == 1) {
        cout << "0\n";
        return 0;
    }
    for (int i = 1; i <= n; i++) {
        for (int x : v[i]) {
            if (cmp[i] != cmp[x]) {
                nv[cmp[i]].push_back(cmp[x]);
                nw[cmp[x]].push_back(cmp[i]);
            }
        }
    }
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < cnt; i++) {
        if (!vis[i]) {
            dfs3(i);
        }
    }
    memset(vis, 0, sizeof(vis));
    vector<pii> par, ans;
    set<int> source, sink;
    for (int x : src) source.insert(x);
    for (int x : snk) sink.insert(x);
    for (int x : src) {
        int match = dfs4(x);
        if (match != -1) {
            par.emplace_back(match, x);
            sink.erase(match);
            source.erase(x);
        }
    }
    int at = par.size();
    for (int i = 0; i < at; i++) ans.emplace_back(rep[par[i].first], rep[par[(i + 1) % at].second]);
    while (!source.empty() && !sink.empty()) {
        a = *sink.begin(), b = *source.begin();
        sink.erase(a), source.erase(b);
        ans.emplace_back(rep[a], rep[b]);
    }
    while (!source.empty()) {
        a = *source.begin();
        source.erase(a);
        ans.emplace_back(ans[0].first, rep[a]);
    }
    while (!sink.empty()) {
        a = *sink.begin();
        sink.erase(a);
        ans.emplace_back(rep[a], ans[0].second);
    }
    cout << ans.size() << '\n';
    for (auto x : ans) cout << x.first << ' ' << x.second << '\n';
    return 0;
}