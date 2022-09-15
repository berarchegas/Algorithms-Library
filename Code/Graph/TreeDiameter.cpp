// Tree diameter
//
// int a = bfs(1, 0);
// int diametro = bfs(a, 1);

vector<int> v[MAXN];
int n;
 
int bfs(int node, bool flag) {
    // flag = true se estou fazendo a segunda BFS
	
    queue<pii> q;
	vector<int> check(n+1);
	check[node] = 1;
	q.push({node, 0});
	int resp = 0, fim = node;
	while (!q.empty()) {
		pii atual = q.front();
		q.pop();
		for (int x : v[atual.first]) {
			if (!check[x]) {
				check[x] = 1;
				q.push({x, atual.second+1});
				if (atual.second + 1 > resp) {
					resp = atual.second + 1;
					fim = x;
				}
			}
		}
	}
	return (flag ? resp : fim);
}