int dep[MAXN], tab[MAXL][MAXN];
vector<int> v[MAXN];

void dfs(int node, int pai = 0) {
    dep[node] = dep[pai] + 1;
    tab[0][node] = pai;
    for (int x : v[node]) {
        if (x != pai) dfs(x, node);
    }
}

void calcTab(int n) {
    for (int i = 1; i < MAXL; i++) {
        for (int j = 1; j <= n; j++) tab[i][j] = tab[i - 1][tab[i - 1][j]]; 
    }
}

int lca(int a, int b) {
    if (dep[a] < dep[b]) swap(a, b);
    for (int i = MAXL - 1; i >= 0; i--) {
        if (dep[a] - (1 << i) >= dep[b]) {
            a = tab[i][a];
        }
    }
    if (a == b) return a;
    for (int i = MAXL - 1; i >= 0; i--) {
        if (tab[i][a] != tab[i][b]) {
            a = tab[i][a];
            b = tab[i][b];
        }
    }
    return tab[0][a];
}