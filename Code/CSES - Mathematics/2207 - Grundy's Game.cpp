// Grundy's Game
//
// Problem name: Grundy's Game
// Problem Link: https://cses.fi/problemset/task/2207
// Author: Bernardo Archegas (https://codeforces.com/profile/Ber)

// There is a heap of n coins and two players who move alternately. 
// On each move, a player chooses a heap and divides into two nonempty heaps that have a different number of coins. 
// The player who makes the last move wins the game.
// Your task is to find out who wins if both players play optimally.

// se n <= 1222, podemos rodar uma dp n ^ 2, se nao o primeiro jogador sempre vence

#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
 
mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());
    
const int MOD = 1e9 + 7;
const int MAXN = 2e5 + 5;
const ll INF = 2e18;
 
vector<int> v = {1,2,4,7,10,20,23,26,50,53,270,273,276,282,285,288,316,334,337,340,346,359,362,365,386,389,392,566,630,633,636,639,673,676,682,685,923,926,929,932,1222,1240};
int ans[1230];
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int cnt = 0;
    for (int i = 1; i <= 1222; i++) {
        if (v[cnt] == i) cnt++;
        else ans[i] = 1;
    }
    int t, n;
    cin >> t;
    while (t--) {
        cin >> n;
        if (n > 1222) cout << "first\n";
        else {
            cout << (ans[n] ? "first\n" : "second\n");
        }
    }
    return 0;
}