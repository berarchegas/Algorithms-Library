// String Transform
//
// Problem name: String Transform
// Problem Link: https://cses.fi/problemset/task/1113
// Author: Bernardo Archegas (https://codeforces.com/profile/Ber)

// Consider the following string transformation:
//     append the character # to the string ('#' < 'a')
//     generate all rotations of the string
//     sort the rotations in increasing order
//     based on this order, construct a new string that contains the last character of each rotation
// For example, the string babc becomes babc#. 
// Then, the sorted list of rotations is #babc, abc#b, babc#, bc#ba, and c#bab. 
// This yields a string cb#ab.
// Given the transformation, reconstruct the original string

#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
 
mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());
    
const int MOD = 1e9 + 7;
const int MAXN = 1e6 + 5;
const ll INF = 2e18;
 
vector<int> pos[27];
int id[27], shift[MAXN];
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    string ini, fim, ans;
    cin >> fim;
    int n = fim.size();
    ini = fim;
    sort(ini.begin(), ini.end());
    for (int i = 0; i < n; i++) {
        if (fim[i] == '#') pos[26].push_back(i);
        else pos[fim[i] - 'a'].push_back(i);
    }
    for (int i = 0; i < n; i++) {
        if (ini[i] == '#') shift[i] = pos[26].back();
        else shift[i] = pos[ini[i] - 'a'][id[ini[i] - 'a']++];
    }
    int at = shift[shift[0]];
    for (int i = 0; i < n - 1; i++) {
        ans += fim[at];
        at = shift[at];
    }
    cout << ans << '\n';
    return 0;
}