// Prufer Code
//
// Problem name: Prufer Code
// Problem Link: https://cses.fi/problemset/task/1134
// Author: Bernardo Archegas (https://codeforces.com/profile/Ber)

// A Prüfer code of a tree of n nodes is a sequence of n - 2 integers that uniquely specifies the structure of the tree.
// The code is constructed as follows: As long as there are at least three nodes left, find a leaf with the smallest label, 
// add the label of its only neighbor to the code, and remove the leaf from the tree.
// Given a Prüfer code of a tree, your task is to construct the original tree.

#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define MAXN 200100
#define INF 1e18
#define pb push_back
#define F first
#define S second
 
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int M = 1e9+7;
 
int c[MAXN], v[MAXN];
 
int main () { _
	int n;
	cin >> n;
	for (int i = 0; i < n-2; i++) {
		cin >> v[i];
		c[v[i]]++;
	}
	priority_queue<int, vector<int>, greater<int>> fila;
	for (int i = 1; i <= n; i++) {
		if (!c[i]) fila.push(i);
	}
	for (int i = 0; i < n-2; i++) {
		cout << fila.top() << ' ' << v[i] << '\n';
		fila.pop();
		c[v[i]]--;
		if (!c[v[i]]) fila.push(v[i]);
	}
	cout << fila.top() << ' ';
	fila.pop();
	cout << fila.top() << '\n';
    return 0;
}