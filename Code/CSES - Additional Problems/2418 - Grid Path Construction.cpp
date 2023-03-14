// Grid Path Construction
//
// Problem name: Grid Path Construction
// Problem Link: https://cses.fi/problemset/task/2418
// Author: Bernardo Archegas (https://codeforces.com/profile/Ber)

// Given an nxm grid and two squares a=(y1,x1) and b=(y2,x2), 
// create a path from a to b that visits each square exactly once.

#include <bits/stdc++.h>
    
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
    
mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());
    
const int MOD = 1e9 + 7;
const int MAXN = 2e5 + 5;
const int INF = 2e9;
 
int dist(int a, int b, int c, int d) {
    return abs(a - c) + abs(b - d);
}
 
bool hamilton(int n, int m, int l1, int c1, int l2, int c2) {
    // recebe linhas, colunas e dois pontos
    // retorna se tem caminho hamiltoniano entre os pontos no grid
 
    int mn = min(n, m), mx = max(n, m);
    int p1 = (l1 + c1) % 2, p2 = (l2 + c2) % 2;
    bool ok = true;
    if ((n * m) % 2 == 0) {
        ok &= (p1 != p2);
        if (mn == 1) {
            ok &= dist(l1, c1, l2, c2) == mx - 1;
        }
        else if (mn == 2) {
            if (n >= m) {
                ok &= (l1 != l2 || l1 == 1 || l1 == n);
            }
            if (n < m) {
                ok &= (c1 != c2 || c1 == 1 || c1 == m);
            }
        }
        else if (mn == 3) {
            if (n >= m) {
                if (p1) {
                    if (c1 == 2 && l1 < l2) ok = false;
                    if (c1 != 2 && l1 < l2 - 1) ok = false;
                }
                if (p2) {
                    if (c2 == 2 && l2 < l1) ok = false;
                    if (c2 != 2 && l2 < l1 - 1) ok = false;
                }
            }
            if (n < m) {
                if (p1) {
                    if (l1 == 2 && c1 < c2) ok = false;
                    if (l1 != 2 && c1 < c2 - 1) ok = false;
                }
                if (p2) {
                    if (l2 == 2 && c2 < c1) ok = false;
                    if (l2 != 2 && c2 < c1 - 1) ok = false;
                }
            }
        }
    }
    if ((n * m) % 2 == 1) {
        ok &= (!p1 && !p2);
        if (mn == 1) {
            ok &= dist(l1, c1, l2, c2) == mx - 1;
        }
    }
    return ok;
}
 
int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
char c[4] = {'D', 'U', 'R', 'L'};
map<char, int> mp = {{'D', 0}, {'U', 1}, {'R', 2}, {'L', 3}};
 
string top;
int check[51][51];
bool valid(int x, int y, int n, int m) { return (x > 0 && x <= n && y > 0 && y <= m && !check[x][y]); }
bool miou(int x, int y, int gx, int gy, int n, int m) {
    if (x == gx && y == gy) return true;
    if (min(n, m) > 2) return false;
    if (valid(x+1, y, n, m) && valid(x-1, y, n, m) && !valid(x, y+1, n, m) && !valid(x, y-1, n, m)) return true;
    if (!valid(x+1, y, n, m) && !valid(x-1, y, n, m) && valid(x, y+1, n, m) && valid(x, y-1, n, m)) return true;
    return false;
}
 
bool run(int x, int y, int gx, int gy, int n, int m) {
    if (top.size() == n * m - 1) return true;
    if (miou(x, y, gx, gy, n, m)) return false;
    check[x][y] = 1;
    bool ok = false;
    for (int i = 0; i < 4; i++) {
        if (valid(x + dx[i], y + dy[i], n, m)) {
            top += c[i];
            ok |= run(x + dx[i], y + dy[i], gx, gy, n, m);
            if (ok) break;
            top.pop_back();
        }
    }
    check[x][y] = 0;
    return ok;
}
 
string brute(int n, int m, int l1, int c1, int l2, int c2) {
    top.clear();
    run(l1, c1, l2, c2, n, m);
    return top;
}
 
void upd(pii *a, char c) {
    a->first += dx[mp[c]];
    a->second += dy[mp[c]];
}
 
string solve(int n, int m, int l1, int c1, int l2, int c2) {
    int mn = min(n, m), mx = max(n, m);
    if ((mn == 1) || (mn == 2) || (mn == 3 && mx == 3) || (mn == 4 && mx <= 5)) {
        // prime grid
        return brute(n, m, l1, c1, l2, c2);
    }
 
    // STRIP
    string ans, nv;
    // dois de cima
    if (n > 3 && l1 > 2 && l2 > 2 && hamilton(n - 2, m, l1 - 2, c1, l2 - 2, c2)) {
        ans = solve(n - 2, m, l1 - 2, c1, l2 - 2, c2);
        pii pos = {l1, c1};
        bool ja = false;
        for (int i = 0; i < (int)ans.size(); i++) {
            if (ans[i] == 'R' && pos.first == 3 && !ja) {
                nv += 'U';
                nv += solve(2, m, 2, pos.second, 2, pos.second + 1);
                nv += 'D';
                ja = true;
                upd(&pos, ans[i]);
                continue;
            }
            if (ans[i] == 'L' && pos.first == 3 && !ja) {
                nv += 'U';
                nv += solve(2, m, 2, pos.second, 2, pos.second - 1);
                nv += 'D';
                ja = true;
                upd(&pos, ans[i]);
                continue;
            }
            nv += ans[i];
            upd(&pos, ans[i]);
        }
        return nv;
    }
 
    // dois de baixo
    if (n > 3 && l1 < n - 1 && l2 < n - 1 && hamilton(n - 2, m, l1, c1, l2, c2)) {
        ans = solve(n - 2, m, l1, c1, l2, c2);
        pii pos = {l1, c1};
        bool ja = false;
        for (int i = 0; i < (int)ans.size(); i++) {
            if (ans[i] == 'R' && pos.first == n - 2 && !ja) {
                nv += 'D';
                nv += solve(2, m, 1, pos.second, 1, pos.second + 1);
                nv += 'U';
                ja = true;
                upd(&pos, ans[i]);
                continue;
            }
            if (ans[i] == 'L' && pos.first == n - 2 && !ja) {
                nv += 'D';
                nv += solve(2, m, 1, pos.second, 1, pos.second - 1);
                nv += 'U';
                ja = true;
                upd(&pos, ans[i]);
                continue;
            }
            nv += ans[i];
            upd(&pos, ans[i]);
        }
        return nv;
    }
 
    // dois da esquerda
    if (m > 3 && c1 > 2 && c2 > 2 && hamilton(n, m - 2, l1, c1 - 2, l2, c2 - 2)) {
        ans = solve(n, m - 2, l1, c1 - 2, l2, c2 - 2);
        pii pos = {l1, c1};
        bool ja = false;
        for (int i = 0; i < (int)ans.size(); i++) {
            if (ans[i] == 'U' && pos.second == 3 && !ja) {
                nv += 'L';
                nv += solve(n, 2, pos.first, 2, pos.first - 1, 2);
                nv += 'R';
                ja = true;
                upd(&pos, ans[i]);
                continue;
            }
            if (ans[i] == 'D' && pos.second == 3 && !ja) {
                nv += 'L';
                nv += solve(n, 2, pos.first, 2, pos.first + 1, 2);
                nv += 'R';
                ja = true;
                upd(&pos, ans[i]);
                continue;
            }
            nv += ans[i];
            upd(&pos, ans[i]);
        }
        return nv;
    }
 
    // dois da direita
    if (m > 3 && c1 < m - 1 && c2 < m - 1 && hamilton(n, m - 2, l1, c1, l2, c2)) {
        ans = solve(n, m - 2, l1, c1, l2, c2);
        pii pos = {l1, c1};
        bool ja = false;
        for (int i = 0; i < (int)ans.size(); i++) {
            if (ans[i] == 'U' && pos.second == m - 2 && !ja) {
                nv += 'R';
                nv += solve(n, 2, pos.first, 1, pos.first - 1, 1);
                nv += 'L';
                ja = true;
                upd(&pos, ans[i]);
                continue;
            }
            if (ans[i] == 'D' && pos.second == m - 2 && !ja) {
                nv += 'R';
                nv += solve(n, 2, pos.first, 1, pos.first + 1, 1);
                nv += 'L';
                ja = true;
                upd(&pos, ans[i]);
                continue;
            }
            nv += ans[i];
            upd(&pos, ans[i]);
        }
        return nv;
    }
 
    // SPLIT
    int p1 = (l1 + c1) % 2, p2 = (l2 + c2) % 2;
 
    // dois de cima
    if (n > 3 && min(l1, l2) <= 2 && max(l1, l2) > 2) {
        if (min(l1, l2) == l1) {
            for (int i = 1 + p1; i <= m; i += 2) {
                if (hamilton(2, m, l1, c1, 2, i) && hamilton(n - 2, m, 1, i, l2 - 2, c2)) {
                    return solve(2, m, l1, c1, 2, i) + 'D' + solve(n - 2, m, 1, i, l2 - 2, c2);
                }
            }
        }
        if (min(l1, l2) == l2) {
            for (int i = 1 + p2; i <= m; i += 2) {
                if (hamilton(n - 2, m, l1 - 2, c1, 1, i) && hamilton(2, m, 2, i, l2, c2)) {
                    return solve(n - 2, m, l1 - 2, c1, 1, i) + 'U' + solve(2, m, 2, i, l2, c2);
                }
            }
        }
    }
    // dois de baixo
    if (n > 3 && max(l1, l2) >= n - 1 && min(l1, l2) < n - 1) {
        if (max(l1, l2) == l1) {
            for (int i = 1 + p1; i <= m; i += 2) {
                if (hamilton(2, m, l1 - n + 2, c1, 1, i) && hamilton(n - 2, m, n - 2, i, l2, c2)) {
                    return solve(2, m, l1 - n + 2, c1, 1, i) + 'U' + solve(n - 2, m, n - 2, i, l2, c2);
                }
            }
        }
        if (max(l1, l2) == l2) {
            for (int i = 1 + p2; i <= m; i += 2) {
                if (hamilton(n - 2, m, l1, c1, n - 2, i) && hamilton(2, m, 1, i, l2 - n + 2, c2)) {
                    return solve(n - 2, m, l1, c1, n - 2, i) + 'D' + solve(2, m, 1, i, l2 - n + 2, c2);
                }
            }
        }
    }
    // dois da esquerda
    if (m > 3 && min(c1, c2) <= 2 && max(c1, c2) > 2) {
        if (min(c1, c2) == c1) {
            for (int i = 1 + p1; i <= n; i += 2) {
                if (hamilton(n, 2, l1, c1, i, 2) && hamilton(n, m - 2, i, 1, l2, c2 - 2)) {
                    return solve(n, 2, l1, c1, i, 2) + 'R' + solve(n, m - 2, i, 1, l2, c2 - 2);
                }
            }
        }
        if (min(c1, c2) == c2) {
            for (int i = 1 + p2; i <= n; i += 2) {
                if (hamilton(n, m - 2, l1, c1 - 2, i, 1) && hamilton(n, 2, i, 2, l2, c2)) {
                    return solve(n, m - 2, l1, c1 - 2, i, 1) + 'L' + solve(n, 2, i, 2, l2, c2);
                }
            }
        }
    }
    // dois da direita
    if (m > 3 && max(c1, c2) >= m - 1 && min(c1, c2) < m - 1) {
        if (min(c1, c2) == c1) {
            for (int i = 1 + p1; i <= n; i += 2) {
                if (hamilton(n, 2, l1, c1 - m + 2, i, 1) && hamilton(n, m - 2, i, m - 2, l2, c2)) {
                    return solve(n, 2, l1, c1 - m + 2, i, 1) + 'L' + solve(n, m - 2, i, m - 2, l2, c2);
				}
			}
		}
		if (min(c1, c2) == c2) {
			for (int i = 1 + p2; i <= n; i += 2) {
				if (hamilton(n, m - 2, l1, c1, i, m - 2) && hamilton(n, 2, i, 1, l2, c2 - m + 2)) {
					return solve(n, m - 2, l1, c1, i, m - 2) + 'R' + solve(n, 2, i, 1, l2, c2 - m + 2);
				}
			}
		}
	}
}
 
int main () {
    ios::sync_with_stdio(false);
    cin.tie(0);
	int t;
	cin >> t;
	while (t--) {
		int n, m, l1, c1, l2, c2;
		cin >> n >> m >> l1 >> c1 >> l2 >> c2;
		if (hamilton(n, m, l1, c1, l2, c2)) {
			cout << "YES\n";
			cout << solve(n, m, l1, c1, l2, c2) << '\n';
		}
		else {
			cout << "NO\n";
		}
	}
    return 0;
}