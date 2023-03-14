// Letter Pair Move Game
//
// Problem name: Letter Pair Move Game
// Problem Link: https://cses.fi/problemset/task/2427
// Author: Bernardo Archegas (https://codeforces.com/profile/Ber)

// There are 2n boxes in a line. Two adjacent boxes are empty, 
// and all other boxes have a letter "A" or "B". Both letters appear in exactly n−1 boxes.
// Your task is to move the letters so that all letters "A" appear before any letter "B". 
// On each turn you can choose any two adjacent boxes that have a letter 
// and move the letters to the two adjacent empty boxes, preserving their order.
// It can be proven that either there is a solution that consists of at most 10n turns 
// or there are no solutions.

#include <bits/stdc++.h>
    
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
    
mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());
    
const int MOD = 1e9 + 7;
const int MAXN = 2e5 + 5;
const int INF = 2e9;
 
int n;
map<vector<char>, pii> mp;
map<vector<char>, bool> vis;
 
bool ok(vector<char> v) {
    int ca = 0;
    bool ja = false;
    for (int i = 0; i < 2 * n; i++) {
        if (v[i] == 'A' && !ja) ca++;
        if (v[i] == 'B') ja = true;
    }
    return ca == n - 1;
}
 
int findPre(vector<char> v) {
    int ca = 0;
    bool ja = false;
    for (int i = 0; i < 2 * n; i++) {
        if (v[i] == 'A' && !ja) ca++;
        if (v[i] == 'B') ja = true;
    }
    return ca;
}
 
int findPos(vector<char> v) {
    int pos;
    for (int i = 0; i < 2 * n - 1; i++) {
        if (v[i] == '.') {
            pos = i;
            break;
        }
    }
    return pos;
}
 
void change(int a, int b, vector<char> &v) {
    swap(v[a], v[b]);
    swap(v[a + 1], v[b + 1]);
}
 
int main () {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    vector<char> v(2 * n);
    for (char &x : v) cin >> x;
    vector<vector<char>> ans;
    if (n < 3) {
        if (ok(v)) cout << "0\n";
        else cout << "-1\n";
    }
    else if (n == 3) {
        queue<vector<char>> fila;
        fila.push(v);
        vector<char> at;
        bool find = false;
        while (!fila.empty()) {
            at = fila.front();
            fila.pop();
            if (ok(at)) {
                find = true;
                break;
            }
            int pos = findPos(at);
            for (int i = 0; i < 2 * n - 1; i++) {
                if (at[i] != '.' && at[i + 1] != '.') {
                    change(i, pos, at);
                    if (!vis[at]) {
                        vis[at] = 1;
                        mp[at] = {i, pos};
                        fila.push(at);
                    }
                    change(i, pos, at);
                }
            }
        }
        if (!find) cout << "-1\n";
        else {
            while (at != v) {
                pii ch = mp[at];
                ans.push_back(at);
                change(ch.first, ch.second, at);
            }
            reverse(ans.begin(), ans.end());
            cout << ans.size() << '\n';
            for (auto y : ans) {
                for (auto x : y) cout << x;
                cout << '\n';
            }
        }
    }
    else {
 
        // primeiro colocar espaco no final
        int pos = findPos(v), pre;
        if (pos == 2 * n - 3) {
            change(0, pos, v);
            ans.push_back(v);
            change(0, pos + 1, v);
            ans.push_back(v);
        }
        else if (pos < 2 * n - 3) {
            change(pos, 2 * n - 2, v);
            ans.push_back(v);
        }
        while (!ok(v)) {
            pre = findPre(v);
            if (pre == n - 2 && v[n - 1] == 'A') {
                // AA ... AABABB ... BB..
                change(n - 1, 2 * n - 2, v);
                ans.push_back(v);
                change(2 * n - 3, n - 1, v);
                ans.push_back(v);
                change(n - 2, 2 * n - 3, v);
                ans.push_back(v);
            }
            else if (pre == n - 3 && v[n - 2] == 'A' && v[2 * n - 3] == 'A') {
                // AA ... AABABB ... BA..
                change(n - 2, 2 * n - 2, v);
                ans.push_back(v);
                change(2 * n - 4, n - 2, v);
                ans.push_back(v);
                change(n - 3, 2 * n - 4, v);
                ans.push_back(v);
                change(2 * n - 2, n - 3, v);
                ans.push_back(v);
            }
            else {
                change(pre, 2 * n - 2, v);
                ans.push_back(v);
                int mudei;
                for (int i = pre + 2; i < 2 * n - 1; i++) {
                    if (v[i] == 'A') {
                        change(i, pre, v);
                        ans.push_back(v);
                        mudei = i;
                        break;
                    }
                }
                if (ok(v)) break;
                change(2 * n - 2, mudei, v);
                ans.push_back(v);
            }
        }
        cout << ans.size() << '\n';
        for (auto y : ans) {
            for (auto x : y) cout << x;
            cout << '\n';
        }
    }
    return 0;
}