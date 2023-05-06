// Monster Game I
//
// Problem name: Monster Game I
// Problem Link: https://cses.fi/problemset/task/2084
// Author: Bernardo Archegas (https://codeforces.com/profile/Ber)

// You are playing a game that consists of n levels. Each level has a monster. 
// On levels 1,2,...,n−1, you can either kill or escape the monster. 
// However, on level n you must kill the final monster to win the game.
// Killing a monster takes s * f time where s is the monster's strength 
// and f is your skill factor (lower skill factor is better). After killing a monster, 
// you get a new skill factor. What is the minimum total time in which you can win the game?
// The first input line has two integers n and x: the number of levels and your initial skill factor.
// The second line has n integers s1 <= s2 <= ...,sn: each monster's strength.
// The third line has n integers f1 >= f2 >= ...,fn: your new skill factor after killing a monster.

#include <bits/stdc++.h>
    
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
    
mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());
    
const int MOD = 1e9 + 7;
const int MAXN = 2e5 + 5;
const ll LINF = 1e18;
 
// Li-Chao Tree
//
// Adiciona retas (ax+b), e computa o minimo entre as retas
// em um dado 'x'
// Cuidado com overflow!
// Se tiver overflow, tenta comprimir o 'x' ou usar
// convex hull trick
//
// O(log(MA-MI)), O(n) de memoria
// 59ba68
 
template<ll MI = ll(-1e9), ll MA = ll(1e9)> struct lichao {
	struct line {
		ll a, b;
		array<int, 2> ch;
		line(ll a_ = 0, ll b_ = LINF) :
			a(a_), b(b_), ch({-1, -1}) {}
		ll operator ()(ll x) { return a*x + b; }
	};
	vector<line> ln;
 
	int ch(int p, int d) {
		if (ln[p].ch[d] == -1) {
			ln[p].ch[d] = ln.size();
			ln.emplace_back();
		}
		return ln[p].ch[d];
	}
	lichao() { ln.emplace_back(); }
 
	void add(line s, ll l=MI, ll r=MA, int p=0) {
		ll m = (l+r)/2;
		bool L = s(l) < ln[p](l);
		bool M = s(m) < ln[p](m);
		bool R = s(r) < ln[p](r);
		if (M) swap(ln[p], s), swap(ln[p].ch, s.ch);
		if (s.b == LINF) return;
		if (L != M) add(s, l, m-1, ch(p, 0));
		else if (R != M) add(s, m+1, r, ch(p, 1));
	}
	ll query(int x, ll l=MI, ll r=MA, int p=0) {
		ll m = (l+r)/2, ret = ln[p](x);
		if (ret == LINF) return ret;
		if (x < m) return min(ret, query(x, l, m-1, ch(p, 0)));
		return min(ret, query(x, m+1, r, ch(p, 1)));
	}
};
 
int s[MAXN], f[MAXN];
ll dp[MAXN];
 
int main () {
    ios::sync_with_stdio(false);
    cin.tie(0);
	int n, x;
    cin >> n >> x;
    for (int i = 1; i <= n; i++) cin >> s[i];
    for (int i = 1; i <= n; i++) cin >> f[i];
    lichao<> ber;
    ber.add(lichao<>::line(x, 0));
    for (int i = 1; i <= n; i++) {
        dp[i] = ber.query(s[i]);
        ber.add(lichao<>::line(f[i], dp[i]));
    }
    cout << dp[n] << '\n';
    return 0;
}