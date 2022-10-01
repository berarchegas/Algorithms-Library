// Broken Profile + Mat Expo
//
#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define MAXN 200100
#define INF 100000000
#define pb push_back
#define F first
#define S second
 
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int M = 998244353;
 
struct mat {
	ll m[65][65];
	mat() {
		for (int i = 0; i < 65; i++) {
			for (int j = 0; j < 65; j++) m[i][j] = 0;
		}
	}
	mat operator * (mat x) {
		mat resp;
		for (int i = 0; i < 65; i++) {
			for (int j = 0; j < 65; j++) {
				resp.m[i][j] = 0;
				for (int k = 0; k < 65; k++) {
					resp.m[i][j] += (m[i][k] * x.m[k][j]) % M;
					if (resp.m[i][j] >= M) resp.m[i][j] -= M;
				}
			}
		}
		return resp;
	}
};
 
mat expo(mat &a, ll e) {
	if (e == 1) return a;
	mat ans = expo(a, e/2);
	ans = ans * ans;
	if (e&1) ans = ans * a;
	return ans;
}
 
int dp[7] = {1, 1, 2, 3, 5, 8, 13};
 
int main () { _
	int h;
	ll w;
	cin >> h >> w;
	mat freitas;
	for (int i = 0; i < (1<<h); i++) {
		for (int j = 0; j < (1<<h); j++) {
			int e = 1, count = 0;
			for (int k = 0; k < h; k++) {
				if (i & (1<<k)) {
					if (j & (1<<k)) e = 0;
					e *= dp[count];
					count = 0;
				}
				else if (j & (1<<k)) {
					e *= dp[count];
					count = 0;
				}
				else count++;
			}
			e *= dp[count];
			freitas.m[j][i] = e;
		}
	}
	freitas = expo(freitas, w);
	cout << freitas.m[0][0] << '\n';
	return 0;
}