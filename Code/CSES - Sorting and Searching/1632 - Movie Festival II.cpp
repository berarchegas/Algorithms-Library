// Movie Festival II
//
// Problem name: Movie Festival II
// Problem Link: https://cses.fi/problemset/task/1632
// Author: Bernardo Archegas (https://codeforces.com/profile/Ber)

// In a movie festival, n movies will be shown. 
// Syrjälä's movie club consists of k members, who will be all attending the festival.
// You know the starting and ending time of each movie. 
// What is the maximum total number of movies the club members can watch entirely if they act optimally?

#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define MAXN 1000100
#define INF 100000000
#define pb push_back
#define F first
#define S second
 
using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
const int M = 1e9+7;
 
int main () { _
    int n, k;
    cin >> n >> k;
    vector<pii> v(n);
    for (int i = 0; i < n; i++) cin >> v[i].S >> v[i].F;
    sort(begin(v), end(v));
    multiset<int> s;
    for (int i = 0; i < k; i++) s.insert(0);
    int resp = 0;
    for (int i = 0; i < n; i++) {
        auto it = s.upper_bound(v[i].S);
        if (it == begin(s)) continue;
        resp++;
        s.erase(--it);
        s.insert(v[i].F);
    }
    cout << resp << '\n';
    return 0;
}