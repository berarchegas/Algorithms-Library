// Birthday
//
// Given a set of strings, we want to find the maximal set of strings
// such that no string in the set is a substring of another string in the set
// Idea: Use Aho-Corasick to build the graph where a and b are connected
// if a is a substring of b
// Then we calculate the transitive closure of this graph, find the maximum antichain
// and recover this antichain

#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
 
mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());
    
const int MOD = 1e9 + 9;
const int MAXN = 1e3 + 5;
const int INF = 1e9;

// Aho-Corasick (Ber)
// 
// tamanho do alfabeto e soma dos tamanhos das strings
const int ALPHA = 2, SIZE = 1e7 + 5;
int I = 1;
 
// nodes do aho
// fail eh o fail link
// ch eh o automato
// podemos colocar mais coisas, tp um inteiro que diz quantas palavras terminam ali
// lembrando que temos que fazer uma dfs pra computar esse inteiro, por exemplo
struct node {
    int fail, nxt, ch[ALPHA] = {}, id = 0;
    bool end;
} T[SIZE];
 
void insert(string s, int i) {
    int x = 1;
    for (int j = 0; j < (int)s.size(); j++) {
        // mudar pra '0' se estivermos lidando com digitos
        if (T[x].ch[s[j] - 'a'] == 0)
            T[x].ch[s[j] - 'a'] = ++I;
        x = T[x].ch[s[j] - 'a'];
    }
    T[x].end |= 1;
    T[x].id = i;
}
 
void build() {
    queue<int> Q;
    int x = 1; 
    T[1].fail = 1;
    T[1].end = 1;
    T[1].id = -1;
    for (int i = 0; i < ALPHA; i++) {
        if (T[x].ch[i])
            T[T[x].ch[i]].fail = x, Q.push(T[x].ch[i]);
        else 
            T[x].ch[i] = 1;
    }
    while (!Q.empty()) {
        x = Q.front(); Q.pop();
        for (int i = 0; i < ALPHA; i++) {
            if (T[x].ch[i])
                T[T[x].ch[i]].fail = T[T[x].fail].ch[i], Q.push(T[x].ch[i]);
            else 
                T[x].ch[i] = T[T[x].fail].ch[i];
        }
        if (T[T[x].fail].end) T[x].nxt = T[T[x].fail].id;
        else T[x].nxt = T[T[x].fail].nxt;
    }
}

set<int> st[800];
vector<int> g[800];
int vis[800];

// rodar uma string pelo automato e computar alguma coisa
void run(string s, int at) {
    for (int i = 0, x = 1; i < s.size(); i++) {
        x = T[x].ch[s[i] - 'a'];
        if (i < s.size() - 1) {
            if (T[x].end)
                st[at].insert(T[x].id);
            else if (T[x].nxt != -1)
                st[at].insert(T[x].nxt);
        }
        else {
            if (T[x].nxt != -1)
                st[at].insert(T[x].nxt);
        }
    }
}

void dfs(int node, int root) {
    vis[node] = 1;
    if (node != root) g[root].push_back(node);
    for (int x : st[node]) 
        if (!vis[x]) dfs(x, root);
}

// Dinic
//
// O(min(m * max_flow, n^2 m))
// Grafo com capacidades 1 -> O(sqrt(n)*m)
// INF ta pra int
struct dinic {
	const bool scaling = false;
	int lim;
	struct edge {
		int to, cap, rev, flow;
		bool res;
		edge(int to_, int cap_, int rev_, bool res_)
			: to(to_), cap(cap_), rev(rev_), flow(0), res(res_) {}
	};

	vector<vector<edge>> g;
	vector<int> lev, beg;
	ll F;
	dinic(int n) : g(n), F(0) {}

	void add(int a, int b, int c) {
		g[a].emplace_back(b, c, g[b].size(), false);
		g[b].emplace_back(a, 0, g[a].size()-1, true);
	}
	bool bfs(int s, int t) {
		lev = vector<int>(g.size(), -1); lev[s] = 0;
		beg = vector<int>(g.size(), 0);
		queue<int> q; q.push(s);
		while (q.size()) {
			int u = q.front(); q.pop();
			for (auto& i : g[u]) {
				if (lev[i.to] != -1 or (i.flow == i.cap)) continue;
				if (scaling and i.cap - i.flow < lim) continue;
				lev[i.to] = lev[u] + 1;
				q.push(i.to);
			}
		}
		return lev[t] != -1;
	}
	int dfs(int v, int s, int f = INF) {
		if (!f or v == s) return f;
		for (int& i = beg[v]; i < g[v].size(); i++) {
			auto& e = g[v][i];
			if (lev[e.to] != lev[v] + 1) continue;
			int foi = dfs(e.to, s, min(f, e.cap - e.flow));
			if (!foi) continue;
			e.flow += foi, g[e.to][e.rev].flow -= foi;
			return foi;
		}
		return 0;
	}
	ll max_flow(int s, int t) {
		for (lim = scaling ? (1<<30) : 1; lim; lim /= 2)
			while (bfs(s, t)) while (int ff = dfs(s, t)) F += ff;
		return F;
	}

	// arestas com fluxo
	vector<pii> flow_edges(int s, int t) {
		max_flow(s, t);
		vector<pii> ans;
		int n = g.size();
		for (int i = 0; i < n; i++) {
			for (auto edge : g[i]) {
				if (!edge.res && edge.flow) 
					ans.emplace_back(i, edge.to);
			}
		}
		return ans;
	}

	// arestas no min cut
	vector<pii> cut_edges(int s, int t) {
		max_flow(s, t);
		vector<pii> cut;
		vector<int> vis(g.size(), 0), st = {s};
		vis[s] = 1;
		while (st.size()) {
			int u = st.back(); st.pop_back();
			for (auto e : g[u]) if (!vis[e.to] and e.flow < e.cap)
				vis[e.to] = 1, st.push_back(e.to);
		}
		for (int i = 0; i < g.size(); i++) for (auto e : g[i])
			if (vis[i] and !vis[e.to] and !e.res) cut.emplace_back(i, e.to);
		return cut;
	}
};

vector<string> v;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    v.resize(n);
    int at = 1;
    for (string &x : v) {
        cin >> x;
        insert(x, at++);
    }
    build();
    at = 1;
    for (string x : v) {
        run(x, at++);
    }
    for (int i = 1; i <= n; i++) {
        dfs(i, i);
        memset(vis, 0, sizeof(vis));
    }

    dinic ber(2 * n + 2);
    for (int i = 1; i <= n; i++) {
        ber.add(0, i, 1);
        for (int x : g[i]) ber.add(i, x + n, INF);
        ber.add(i + n, 2 * n + 1, 1);
    }
    vector<pii> ed = ber.cut_edges(0, 2 * n + 1);
    set<int> antichain;
    for (int i = 1; i <= n; i++) antichain.insert(i);
    for (pii x : ed) {
        if (x.first == 0) antichain.erase(x.second);
        else antichain.erase(x.first - n);
    }
    cout << antichain.size() << '\n';
    for (int x : antichain) cout << x << ' ';
    cout << '\n';
    return 0;
}