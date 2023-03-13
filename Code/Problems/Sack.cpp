// Sack
//
// Lomsat Gelral
// Given a tree where every node has a color
// You have to find for every vertex the sum of dominanting colors
// of the subtree of that vertex
// A color is dominating a subtree if no other color appears more than that color
// Which means that more than one color can dominate

#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
 
mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());
    
const int MOD = 1e9 + 7;
const int MAXN = 1e5 + 5;
const ll INF = 2e18;

vector<int> v[MAXN];
int cnt[MAXN], cor[MAXN], sz[MAXN], vsf;
ll ans[MAXN], qtd[MAXN];
bool big[MAXN];

int calcSz(int node, int pai) {
    sz[node] = 1;
    for (int x : v[node]) {
        if (x != pai) {
            sz[node] += calcSz(x, node);
        }
    }
    return sz[node];
}

// This is specific to the sack problem
void add(int node, int pai, int val) {
    qtd[cnt[cor[node]]] -= cor[node];
    cnt[cor[node]] += val;
    vsf = max(vsf, cnt[cor[node]]);
    qtd[cnt[cor[node]]] += cor[node];
    if (vsf && !qtd[vsf]) vsf--;
    for (int x : v[node]) {
        if (x != pai && !big[x]) {
            add(x, node, val);
        }
    }
}

void dfs(int node, int pai, bool keep) {
	// Find the bigChild
    int mx = -1, bigChild = -1;
    for (int x : v[node]) {
        if (x != pai && sz[x] > mx) {
            mx = sz[x], bigChild = x;
        }
    }
    // Find the answer for every small child and clear them from cnt
    for (int x : v[node]) {
        if (x != pai && x != bigChild) {
            dfs(x, node, 0);
        }
    }
    // Find the answer for the bigChild and maintain it in cnt
    // Mark the bigChild as big so that you dont add it to cnt again on add(node, pai, 1)
    if (bigChild != -1)
        dfs(bigChild, node, 1), big[bigChild] = 1;
    
    // Add the rest of the subtree of node to cnt
    add(node, pai, 1);
    // Save the answer
    ans[node] = qtd[vsf];
    if (bigChild != -1)
        big[bigChild] = 0;
    if(keep == 0)
        add(node, pai, -1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, a, b;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> cor[i];
    for (int i = 0; i < n - 1; i++) {
        cin >> a >> b;
        v[a].push_back(b);
        v[b].push_back(a);
    }
    // First Calculate the size of every subtree
    calcSz(1, 0);
    // Dfs to calculate the answer
    dfs(1, 0, 0);
    for (int i = 1; i <= n; i++) cout << ans[i] << ' ';
    cout << '\n';
    return 0;
}