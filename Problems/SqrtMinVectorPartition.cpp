#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 10;
const int SQ = 326;
int v[MAXN], mx[SQ], bl[MAXN], e[SQ], d[SQ];
int main() {
	for(int i = 0; i < SQ; i++) e[i] = MAXN;
	for(int i = 0; i < MAXN; i++) {
		bl[i] = i / SQ;
		e[bl[i]] = min(i, e[bl[i]]);
		d[bl[i]] = max(d[bl[i]], i);
	}
	int t;
	scanf("%d", &t);
	for(int ab = 0; ab < t; ab++) {
		printf("Scenario #%d:\n", ab + 1);
		int n, q;
		for(int i = 0; i < SQ; i++) {
			mx[i] = 1123456789;
		}
		scanf("%d %d", &n, &q);
		for(int i = 0; i < n; i++) {
			scanf("%d", &v[i]);
			mx[bl[i]] = min(mx[bl[i]], v[i]);
		}
		for(int i = 0; i < q; i++) {
			int a, b;
			scanf("%d %d", &a, &b); a--; b--;
			int resp = 1123456789;
			if(bl[a] == bl[b]) {
				for(int j = a; j <= b; j++) {
					resp = min(v[j], resp);
				}
			}
			else {
				for(int j = a; j <= d[bl[a]]; j++) {
					resp = min(resp, v[j]);
				}
				for(int j = b; j >= e[bl[b]]; j--) {
					resp = min(resp, v[j]);
				}
				for(int j = bl[a] + 1; j <= bl[b] - 1; j++) {
					resp = min(mx[j], resp);
				}
			}
			printf("%d\n", resp);
		}
	}
	return 0;
} 