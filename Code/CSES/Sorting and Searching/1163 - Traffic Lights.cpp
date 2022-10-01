// Traffic Lights
//
// Problem name: Traffic Lights
// Problem Link: https://cses.fi/problemset/task/1163
// Author: Bernardo Archegas (https://codeforces.com/profile/Ber)

// There is a street of length x whose positions are numbered 0,1... x. 
// Initially there are no traffic lights, but n sets of traffic lights are added to the street one after another.
// Your task is to calculate the length of the longest passage without traffic lights after each addition.

#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define MAXN 100100
#define INF 1000000001
#define pb push_back
#define F first
#define S second
 
using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
const int M = 1e9 + 7;
 
set<int> luz;
multiset<int> dist;
 
int main() { _
    int x, n, aux;
    cin >> x >> n;
    luz.insert(0), luz.insert(x);
    dist.insert(x);
    for (int i = 0; i < n; i++) {
        cin >> aux;
        auto it1 = luz.upper_bound(aux);
        auto it2 = it1;
        it2--;
        dist.erase(dist.find(*it1 - *it2));
        dist.insert(*it1 - aux), dist.insert(aux - *it2);
        luz.insert(aux);
        it1 = dist.end(), it1--;
        cout << *it1 << ' ';
    }
    cout << '\n';
    return 0;
}