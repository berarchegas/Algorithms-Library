// Two Stacks Sorting
//
// Problem name: Two Stacks Sorting
// Problem Link: https://cses.fi/problemset/task/2402
// Author: Bernardo Archegas (https://codeforces.com/profile/Ber)

// You are given an input list that consists of n numbers. Each integer between 1 and n appears exactly once in the list.
// Your task is to create a sorted output list using two stacks. On each move you can do one of the following:
//     Move the first number from the input list to a stack
//     Move a number from a stack to the end of the output list

#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
 
mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());
    
const int MOD = 1e9 + 7;
const int MAXN = 2e5 + 5;
const ll INF = 2e18;
 
struct no {
    int mn, mx;
    no(int _mn = MAXN, int _mx = 0) {
        mn = _mn, mx = _mx;
    }
    no operator + (const no &x) const {
        no aux;
        aux.mn = min(mn, x.mn);
        aux.mx = max(mx, x.mx);
        return aux;
    }
} a[4 * MAXN];
 
pii tree[MAXN];
 
void build(int node, int i, int j) {
    if (i == j) {
        a[node] = no(tree[i].first, tree[i].second);
    }
    else {
        int m = (i + j) / 2;
        build(2 * node, i, m);
        build(2 * node + 1, m + 1, j);
        a[node] = a[2 * node] + a[2 * node + 1];
    }
}
 
void update(int node, int i, int j, int pos) {
    if (i == j) {
        a[node] = no(tree[i].first, tree[i].second);
    }
    else {
        int m = (i + j) / 2;
        if (pos <= m)
            update(2 * node, i, m, pos);
        else
            update(2 * node + 1, m + 1, j, pos);
        a[node] = a[2 * node] + a[2 * node + 1];
    }
}
 
no query(int node, int i, int j, int ini, int fim) {
    if (ini > j || fim < i) return no(MAXN, 0);
    else if (ini <= i && j <= fim) return a[node];
    else {
        int m = (i + j) / 2;
        return query(2 * node, i, m, ini, fim) + query(2 * node + 1, m + 1, j, ini, fim);
    }
}
 
int v[MAXN], cor[MAXN], great[MAXN], vis[MAXN], pos[MAXN];
vector<int> g[MAXN];
 
void dfs(int node, int c) {
    cor[node] = c;
    vis[node] = 1;
    for (int x : g[node]) {
        if (!vis[x]) {
            dfs(x, c ^ 1);
        }
    }
}
 
bool check(int n) {
    stack<int> s[2];
    int at = 1;
    for (int i = 1; i <= n; i++) {
        s[cor[i]].push(v[i]);
        while (!s[0].empty() && s[0].top() == at) {
            s[0].pop();
            at++;
            while (!s[1].empty() && s[1].top() == at) {
                s[1].pop();
                at++;
            }
        }
        while (!s[1].empty() && s[1].top() == at) {
            s[1].pop();
            at++;
            while (!s[0].empty() && s[0].top() == at) {
                s[0].pop();
                at++;
            }
        }
    }
    return s[0].empty() && s[1].empty();
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> v[i];
    v[n + 1] = n + 1;
    for (int i = 1; i <= n; i++) {
        tree[i] = {v[i], 0};
        pos[v[i]] = i;
    }
    for (int i = 1; i <= n; i++) great[i] = i + 1;
    for (int i = n; i >= 1; i--) {
        while (v[great[i]] < v[i]) {
            great[i] = great[great[i]];
        }
    }
    build(1, 1, n);
    no aux, giuli;
    for (int i = 1; i < n; i++) {
        if (great[i] < n) {
            aux = query(1, 1, n, great[i] + 1, n);
            if (aux.mn < v[i]) {
                g[i].push_back(great[i]);
                g[great[i]].push_back(i);
            }
        }
        if (v[i] > 1) {
            aux = query(1, 1, n, 1, v[i] - 1);
            if (aux.mx) {
                giuli = query(1, 1, n, i + 1, n);
                if (giuli.mn < aux.mx) {
                    g[pos[aux.mx]].push_back(i);
                    g[i].push_back(pos[aux.mx]);
                }
            }
        }
        tree[v[i]].second = v[i];
        update(1, 1, n, v[i]);
    }
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) dfs(i, 0);
    }
    if (check(n)) {
        for (int i = 1; i <= n; i++) cout << cor[i] + 1 << ' ';
        cout << '\n';
    }
    else cout << "IMPOSSIBLE\n";
    return 0;
}