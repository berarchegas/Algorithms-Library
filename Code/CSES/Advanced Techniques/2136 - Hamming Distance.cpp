// Hamming Distance
//
// Problem name: Hamming Distance
// Problem Link: https://cses.fi/problemset/task/2136
// Author: Bernardo Archegas (https://codeforces.com/profile/Ber)

// The Hamming distance between two strings a and b of equal length is the number of positions where the strings differ.
// You are given n bit strings, each of length k and your task is to calculate the minimum Hamming distance between two strings. 

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
 
int main() { _
    int n, k;
	cin >> n >> k;
	vector<pii> v(n);
	string s;
	for (int i = 0; i < n; i++) {
		cin >> s;
		v[i].F = stoi(s, nullptr, 2);
	}	
	int resp = k+1;
	v[0].S = resp;
	for (int i = 1; i < n; i++) {
		v[i].S = __builtin_popcount(v[0].F ^ v[i].F);
		resp = min(resp, v[i].S);
	}
	sort(v.begin(), v.end(), [&](pii a, pii b) { return a.S < b.S; } );
	for (int i = 1; i < n; i++) {
		for (int j = i+1; j < n; j++) {
			if (v[j].S < v[i].S + resp) {
				resp = min(resp, __builtin_popcount(v[j].F ^ v[i].F));
			}
			else break;
		}
	}
	cout << resp << '\n';
    return 0;
}