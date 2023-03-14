// Distinct Colors
//
// Problem name: Distinct Colors
// Problem Link: https://cses.fi/problemset/task/1139
// Author: Bernardo Archegas (https://codeforces.com/profile/Ber)

// You are given a rooted tree consisting of n nodes. 
// The nodes are numbered 1,2 ... n, and node 1 is the root. Each node has a color.
// Your task is to determine for each node the number of distinct colors in the subtree of the node.

#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define MAXN 200100
#define INF 1000000001
#define pb push_back
#define F first
#define S second
 
using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
const int M = 1e9+7;
 
vector<int> v[MAXN];
int c[MAXN], ans[MAXN];
set<int> s[MAXN];
 
void dfs(int node, int pai) {
    s[node].insert(c[node]);
    for (int x : v[node]) {
        if (x != pai) {
            dfs(x, node);
            if ((int)s[x].size() > (int)s[node].size()) swap(s[x], s[node]);
            for (int y : s[x]) s[node].insert(y);
        }
    }
    ans[node] = (int)s[node].size();
}
 
int main () { _
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> c[i];
    for (int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b;
        v[a].pb(b);
        v[b].pb(a);
    }
    dfs(1, 0);
    for (int i = 1; i <= n; i++) cout << ans[i] << ' ';
    cout << '\n';
	return 0;	
}