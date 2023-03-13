// Graph Connectivity
//
// Given a Graph, we want to find what is the minimum ammount of vertices 
// we have to erase in order to disconnect the graph
// We can solve this with Menger's Theorem, and then we check a good enough ammount
// of pairs of vertices and check if the max flow between them is >= k
// If yes, then the graph is k-connected

// In this specific problem, we wanted to check if k was >= n/2
// Ideia: Para que G seja Strongly Matchable, todo subconjunto S deve ter N(S) >= n/2
// Isso ocorre sse o grafo for k-conexo com k >= n/2
// Pra verificar se um grafo é k-conexo usamos fluxo pra ver se tem k caminhos disjuntos entre todo par de nó
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m, a, b;
    cin >> n >> m;
    dinic g(2 * n);
    for (int i = 0; i < n; i++) {
        g.add(i, i + n, 1);
    }
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        a--, b--;
        g.add(a + n, b, 1);
        g.add(b + n, a, 1);
    }
    bool ok = true;
    for (int i = 0; i < 7; i++) {
        int a = rng() % n;
        for (int j = 0; j < n; j++) {
            if (a == j) continue;
            dinic h = g;
            ok &= h.max_flow(a + n, j) >= n / 2;
        }
    }
    cout << (ok ? 1 : -1) << '\n';
    return 0;
}