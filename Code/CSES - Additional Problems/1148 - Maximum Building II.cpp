// Maximum Building II
//
// Problem name: Maximum Building II
// Problem Link: https://cses.fi/problemset/task/1148
// Author: Bernardo Archegas (https://codeforces.com/profile/Ber)

// You are given a map of a forest where some squares are empty and some squares have trees.
// You want to place a rectangular building in the forest so that no trees need to be cut down. 
// For each building size, your task is to calculate the number of ways you can do this.

#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
 
mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());
    
const int MOD = 1e9 + 7;
const int MAXN = 1e3 + 5;
const ll INF = 2e18;
 
int mat[MAXN][MAXN], v[MAXN][MAXN], w[MAXN];
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    char c;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> c;
            if (c == '*') v[i][j] = 0;
            else v[i][j] = 1;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (v[i][j]) w[j]++;
            else w[j] = 0;
        }
        vector<pii> sk;
        if (w[1]) 
            sk.emplace_back(w[1], 1);
        for (int j = 2; j <= m + 1; j++) {
            int st = 1;
            while (!sk.empty() && sk.back().first > w[j]) {
                int alt = sk.back().first, tam = sk.back().second;
                mat[alt][tam]++;
                sk.pop_back();
                if (!sk.empty() && sk.back().first > w[j]) {
                    mat[sk.back().first][tam]--;
                    sk.back().second += tam;
                }
                else {
                    st += tam;
                    mat[w[j]][tam]--;
                }
            }
            if (!sk.empty() && sk.back().first == w[j]) {
                sk.back().second += st;
            }
            else if (w[j]) {
                sk.emplace_back(w[j], st);
            }
        }
    }
    for (int j = 1; j <= m; j++) {
        for (int i = n - 1; i >= 1; i--) mat[i][j] += mat[i + 1][j];
    }
    for (int go = 0; go < 2; go++) {
        for (int i = 1; i <= n; i++) {
            for (int j = m - 1; j >= 1; j--) mat[i][j] += mat[i][j + 1];
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) cout << mat[i][j] << ' ';
        cout << '\n';
    }
    return 0;
}