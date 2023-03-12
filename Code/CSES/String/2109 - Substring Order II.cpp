// Substring Order II
//
// Problem name: Substring Order II
// Problem Link: https://cses.fi/problemset/task/2109
// Author: Bernardo Archegas (https://codeforces.com/profile/Ber)

// You are given a string of length n. 
// If all of its substrings (not necessarily distinct) are ordered lexicographically, 
// what is the kth smallest of them?

#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
 
mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());
    
const int MOD = 1e9 + 7;
const int MAXN = 1e5 + 5;
const ll INF = 2e18;
 
const int MAXB = 20;
 
struct suffix_array{
    const int alpha = 300;
 
    int c[MAXB][MAXN] , p[MAXN] , cn[MAXN] , pn[MAXN] , cnt[MAXN];
    string s;
 
    void suffix_ini(){
        memset(cnt,0,sizeof cnt);
        memset(c,-1,sizeof c);
 
        int n = s.size();
 
        for(int i = 0;i < n;i++) cnt[s[i]] ++;
        for(int i = 1;i < alpha;i++) cnt[i] += cnt[i - 1];
        for(int i = n - 1;i >= 0;i--) p[--cnt[s[i]]] = i;
 
        int cla = 0;
        c[0][p[0]] = 0;
 
        for(int i = 1;i < n;i++){
            if(s[p[i]] != s[p[i - 1]]) ++cla;
            c[0][p[i]] = cla;
        }
    }
 
    void suffix(){
        int n = s.size();
 
        for(int h = 0;(1 << h) < n;h++){
            for(int i = 0;i < n;i++){
                pn[i] = p[i] - (1 << h);
                if(pn[i] < 0) pn[i] += n;
            }
 
            memset(cnt,0,sizeof cnt);
 
            for(int i = 0;i < n;i++) cnt[c[h][pn[i]]] ++;
            for(int i = 0;i < n;i++) cnt[i] += cnt[i - 1];
            for(int i = n - 1;i >= 0;i--) p[--cnt[c[h][pn[i]]]] = pn[i];
 
            int cla = 0;
            cn[p[0]] = 0;
 
            for(int i = 1;i < n;i++){
                pair<int,int> cur = {c[h][p[i]],c[h][(p[i] + (1 << h)) % n]};
                pair<int,int> pre = {c[h][p[i - 1]],c[h][(p[i - 1] + (1 << h)) % n]};
 
                if(cur.first != pre.first || cur.second != pre.second) cla ++;
                cn[p[i]] = cla;
            }
 
            for(int i = 0;i < n;i++) c[h + 1][i] = cn[i];
        }
    }
 
    void sdo(string S){
        s = S;
        s += "&";
        suffix_ini();
        suffix();
    }
 
    int comp(int x,int y){
        int res = 0;
        int n = s.size();
 
        for(int i = MAXB - 1;i >= 0;i--){
            if(c[i][x] == -1 || c[i][y] == -1 || c[i][x] != c[i][y])
                continue;
 
            x += (1 << i);
            y += (1 << i);
            res += (1 << i);
 
            if(x >= n)
                x -= n;
            if(y >= n)
                y -= n;            
        }
 
        return res;
    }
 
    void printP(){
        cout << s << endl;
        for(int i = 0;i < s.size();i++){
            cout << p[i] << " ";
        }
        cout << endl;
    }
};
 
suffix_array sa;
ll pre[MAXN];
vector<int> v[MAXN];
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    string s;
    cin >> s;
    sa.sdo(s);
    int n = s.size();
    for (int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + n - sa.p[i];
    }
    for (int i = 2; i <= n; i++) {
        int c = sa.comp(sa.p[i], sa.p[i - 1]);
        v[c].push_back(i - 1);
    }
    ll find;
    cin >> find;
    int l = 1, r = n, tam;
    for (int i = 0; i < n; i++) {
        
        // soh temos strings > i no range
        for (int x : v[i]) {
            if (x < l || x > r) continue;
        
            // processar os lcp´s iguais a i
            ll temos = pre[x] - pre[l - 1] - (x - l + 1ll) * i;
            if (find > temos) {
                find -= temos;
                l = x + 1;
            }
            else {
                r = x;
                break;
            }
        }
        find -= r - l + 1;
        tam = i + 1;
        if (find <= 0) break;
    }
    for (int i = 0; i < tam; i++) cout << s[sa.p[l] + i];
    cout << '\n';
    return 0;
}