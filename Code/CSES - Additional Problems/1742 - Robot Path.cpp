// Robot Path
//
// Problem name: Robot Path
// Problem Link: https://cses.fi/problemset/task/1742
// Author: Bernardo Archegas (https://codeforces.com/profile/Ber)

// You are given a description of a robot's path. 
// The robot begins at point (0,0) and performs n commands. 
// Each command moves the robot some distance up, down, left or right.
// The robot will stop when it has performed all commands, 
// or immediately when it returns to a point that it has already visited. 
// Your task is to calculate the total distance the robot moves.

#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
 
mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());
    
const int MOD = 1e9 + 7;
const int MAXN = 1e5 + 5;
const ll INF = 2e18;
 
struct line {
	int x1, x2, y1, y2, take;
    line(int _x1 = 0, int _y1 = 0, int _x2 = 0, int _y2 = 0, int _take = 0) {
        x1 = _x1, y1 = _y1, x2 = _x2, y2 = _y2, take = _take;
    }
};
 
ll bit[MAXN];
 
void upd(int pos, int val) {pos += 2; for (; pos < MAXN; pos += (pos & -pos)) bit[pos] += val; }
 
ll sum(int pos) {
    pos += 2;
	ll ans = 0;
	for (; pos; pos -= (pos & -pos)) ans += bit[pos];
	return ans;
}
 
vector<line> hor[MAXN], vert[MAXN], chor[MAXN];
 
bool opp(char a, char b) {
    return (a == 'L' && b == 'R') || (a == 'R' && b == 'L') || (a == 'U' && b == 'D') || (a == 'D' && b == 'U');
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<pair<char, ll>> v;
    pair<char, ll> aux;
    ll l = 0, r = 0;
    bool stop = false;
    for (int i = 0; i < n; i++) {
        cin >> aux.first >> aux.second;
        if (i) {
            if (opp(aux.first, v.back().first)) stop = true;
            if (!stop) {
                if (aux.first == v.back().first) v.back().second += aux.second;
                else v.push_back(aux);
            }
        }
        else v.push_back(aux);
        if (!stop) r += aux.second;
    }
    n = v.size();
    while (r > l + 1) {
        ll m = (l + r) / 2, andei = 0, at, linhas = 0;
        vector<ll> x, y;
        pll a = {0, 0};
        x.push_back(0), y.push_back(0);
        for (int i = 0; i < n; i++) {
            linhas++;
            if (m - andei <= v[i].second) {
                at = m - andei;
            }
            else {
                at = v[i].second;
            }
            if (v[i].first == 'L') {
                x.push_back(a.first - at);
                a.first -= at;
            }
            if (v[i].first == 'R') {
                x.push_back(a.first + at);
                a.first += at;
            }
            if (v[i].first == 'U') {
                y.push_back(a.second + at);
                a.second += at;
            }
            if (v[i].first == 'D') {
                y.push_back(a.second - at);
                a.second -= at;
            }
            if (at == m - andei) break;
            andei += at;
        }
        sort(x.begin(), x.end());
        x.erase(unique(x.begin(), x.end()), x.end());
        sort(y.begin(), y.end());
        y.erase(unique(y.begin(), y.end()), y.end());
 
        // x1 < x2, y1 < y2
        int x1, x2, y1, y2;
        andei = 0;
        a = {0, 0};
        for (int i = 0; i < n; i++) {
            if (m - andei <= v[i].second) {
                at = m - andei;
            }
            else {
                at = v[i].second;
            }
            if (v[i].first == 'L') {
                x1 = lower_bound(x.begin(), x.end(), a.first - at) - x.begin();
                x2 = lower_bound(x.begin(), x.end(), a.first) - x.begin();
                y1 = y2 = lower_bound(y.begin(), y.end(), a.second) - y.begin();
                hor[x1].emplace_back(x1, y1, x2, y2, 1);
                chor[y1].emplace_back(x1, y1, x2, y2, 1);
                a.first -= at;
            }
            if (v[i].first == 'R') {
                x1 = lower_bound(x.begin(), x.end(), a.first) - x.begin();
                x2 = lower_bound(x.begin(), x.end(), a.first + at) - x.begin();
                y1 = y2 = lower_bound(y.begin(), y.end(), a.second) - y.begin();
                hor[x1].emplace_back(x1, y1, x2, y2, 1);
                chor[y1].emplace_back(x1, y1, x2, y2, 1);
                a.first += at;
            }
            if (v[i].first == 'U') {
                y1 = lower_bound(y.begin(), y.end(), a.second) - y.begin();
                y2 = lower_bound(y.begin(), y.end(), a.second + at) - y.begin();
                x1 = x2 = lower_bound(x.begin(), x.end(), a.first) - x.begin();
                vert[x1].emplace_back(x1, y1, x2, y2, 1);
                a.second += at;
            }
            if (v[i].first == 'D') {
                y1 = lower_bound(y.begin(), y.end(), a.second - at) - y.begin();
                y2 = lower_bound(y.begin(), y.end(), a.second) - y.begin();
                x1 = x2 = lower_bound(x.begin(), x.end(), a.first) - x.begin();
                vert[x1].emplace_back(x1, y1, x2, y2, 1);
                a.second -= at;
            }
            if (at == m - andei) break;
            andei += at;
        }
        bool ok = true;
 
        // checar se tem intersecao entre segmento paralelo
        for (int i = 0; i <= n; i++) {
            sort(chor[i].begin(), chor[i].end(), [&] (line a, line b) {
                return a.x1 < b.x1;
            });
            sort(vert[i].begin(), vert[i].end(), [&] (line a, line b) {
                return a.y1 < b.y1;
            });
            ll mn = -1e9;
            for (auto ber : chor[i]) {
                ok &= ber.x1 > mn;
                mn = ber.x2;
            }
            mn = -1e9;
            for (auto ber : vert[i]) {
                ok &= ber.y1 > mn;
                mn = ber.y2;
            }
        }
 
        // contar intersecao entre segmento geral
        ll ans = 0;
        for (int i = 0; i < MAXN; i++) {
            for (line &x : hor[i]) {
                if (x.take == 1) {
                    // cout << "SOMA " << x.x1 << ' ' << x.y1 << ' ' << x.x2 << ' ' << x.y2 << '\n'; 
                    upd(x.y1, x.take);  
                    x.take = -1;
                    hor[x.x2].push_back(x);
                    x.take = 1;
                }
            }
            for (line &x : vert[i]) {
                ans += sum(x.y2) - sum(x.y1-1);
            }
            for (line &x : hor[i]) {
                if (x.take == -1) {
                    upd(x.y1, x.take);  
                }
            }
        }
        ok &= (ans == linhas - 1);
 
        for (int i = 0; i < MAXN; i++) {
            bit[i] = 0;
            vert[i].clear();
            hor[i].clear();
            chor[i].clear();
        }
 
        if (ok) l = m;
        else r = m;
    }
    cout << l + 1 << '\n';
    return 0;
}