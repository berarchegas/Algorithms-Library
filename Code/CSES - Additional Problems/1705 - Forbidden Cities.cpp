// Forbidden Cities
//
// Problem name: Forbidden Cities
// Problem Link: https://cses.fi/problemset/task/1705
// Author: Bernardo Archegas (https://codeforces.com/profile/Ber)

// There are n cities and m bidirectional roads between them
// You are given q queries of the form a, b, c
// For each query, answer if it is possible to travel from city a to city b without going through city c

#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
 
mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());
    
const int MOD = 1e9 + 7;
const int MAXN = 2e5 + 5;
const ll INF = 2e18;
 
// Block-Cut Tree
//
// Cria a block-cut tree, uma arvore com os blocos
// e os pontos de articulacao
// Blocos sao componentes 2-vertice-conexos maximais
// Uma 2-coloracao da arvore eh tal que uma cor sao
// os blocos, e a outra cor sao os pontos de art.
// Funciona para grafo nao conexo
//
// art[i] responde o numero de novas componentes conexas
// criadas apos a remocao de i do grafo g
// Se art[i] >= 1, i eh ponto de articulacao
// 
// Para todo i <= blocks.size()
// blocks[i] eh uma componente 2-vertce-conexa maximal
// edgblocks[i] sao as arestas do bloco i
// tree[i] eh um vertice da arvore que corresponde ao bloco i
// 
// pos[i] responde a qual vertice da arvore vertice i pertence
// Arvore tem no maximo 2n vertices
//
// O(n+m)
// 056fa2
 
struct block_cut_tree {
	vector<vector<int>> g, blocks, tree;
	vector<vector<pair<int, int>>> edgblocks;
	stack<int> s;
	stack<pair<int, int>> s2;
	vector<int> id, art, pos;
	
	block_cut_tree(vector<vector<int>> g_) : g(g_) {
		int n = g.size();
		id.resize(n, -1), art.resize(n), pos.resize(n);
		build();
	}
 
	int dfs(int i, int& t, int p = -1) {
		int lo = id[i] = t++;
		s.push(i);	
		
		if (p != -1) s2.emplace(i, p);
		for (int j : g[i]) if (j != p and id[j] != -1) s2.emplace(i, j);
		
		for (int j : g[i]) if (j != p) {
			if (id[j] == -1) {
				int val = dfs(j, t, i);
				lo = min(lo, val);
 
				if (val >= id[i]) {
					art[i]++;
					blocks.emplace_back(1, i);
					while (blocks.back().back() != j) 
						blocks.back().push_back(s.top()), s.pop();
 
					edgblocks.emplace_back(1, s2.top()), s2.pop();
					while (edgblocks.back().back() != pair(j, i))
						edgblocks.back().push_back(s2.top()), s2.pop();
				}
				// if (val > id[i]) aresta i-j eh ponte
			}
			else lo = min(lo, id[j]);
		}
		
		if (p == -1 and art[i]) art[i]--;
		return lo;
	}
 
	void build() {
		int t = 0;
		for (int i = 0; i < g.size(); i++) if (id[i] == -1) dfs(i, t, -1);
		
		tree.resize(blocks.size());
		for (int i = 0; i < g.size(); i++) if (art[i]) 
			pos[i] = tree.size(), tree.emplace_back();
 
		for (int i = 0; i < blocks.size(); i++) for (int j : blocks[i]) {
			if (!art[j]) pos[j] = i;
			else tree[i].push_back(pos[j]), tree[pos[j]].push_back(i);
		}
	}
};
 
int tab[20][MAXN], dep[MAXN];
vector<vector<int>> g;
 
int lca(int a, int b) {
    if (dep[a] < dep[b]) swap(a, b);
    for (int i = 19; i >= 0; i--) {
        if (dep[a] - (1 << i) >= dep[b]) a = tab[i][a];
    }
    if (a == b) return a;
    for (int i = 19; i >= 0; i--) {
        if (tab[i][a] != tab[i][b]) {
            a = tab[i][a], b = tab[i][b];
        }
    }
    return tab[0][a];
}
 
void dfs(int node, int pai, block_cut_tree &ber) {
    dep[node] = dep[pai] + 1;
    tab[0][node] = pai;
    for (int i = 1; i < 20; i++) tab[i][node] = tab[i - 1][tab[i - 1][node]];
    for (int x : ber.tree[node]) {
        if (x != pai)
            dfs(x, node, ber);
    }
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m, q, a, b, c;
    cin >> n >> m >> q;
    g.resize(n);
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        a--, b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    block_cut_tree ber(g);
    dfs(ber.pos[0], ber.pos[0], ber);
    for (int i = 0; i < q; i++) {
        cin >> a >> b >> c;
        a--, b--, c--;
        if (a == c || b == c) cout << "NO\n";
        else if (!ber.art[c]) cout << "YES\n";
        else {
            a = ber.pos[a], b = ber.pos[b], c = ber.pos[c];
            int x = lca(a, b), y = lca(a, c), z = lca(b, c);
            if (x == c || (y == x && z == c) || (z == x && y == c)) cout << "NO\n";
            else cout << "YES\n"; 
        }
    }
    return 0;
}
