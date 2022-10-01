// Convex Hull Trick
//
#include<bits/stdc++.h>
	
using namespace std;
const int MAXN = 100100;
	
#define int long long
	
int t[MAXN];
int a[MAXN],b[MAXN];
int dp[MAXN];
	
int comp(int a,int c,int x){
	if(dp[a] + b[a] * x >= dp[c] + b[c] * x) return 1;
	return 0;
}
	
double f(int x,int y){
	return double(dp[x] - dp[y]) / double(b[y] - b[x]);
}
	
signed main(){
	int n;
	cin >> n;
	
	for(int i = 1;i <= n;i++) cin >> a[i];
	for(int i = 1;i <= n;i++) cin >> b[i];
	
	// dp[i] = dp[j] + bj * ai 
	
	int ini = 1,fim = 1;
	t[1] = 1;
	dp[1] = 0;
	
	for(int i = 2;i <= n;i++){
		while(ini < fim && comp(t[ini],t[ini + 1],a[i]) == 1) ini ++;
		dp[i] = dp[t[ini]] + b[t[ini]] * a[i];
		while(ini < fim && f(i,t[fim]) <= f(t[fim],t[fim - 1])) fim --;
		t[++fim] = i;
	}
	
	cout << dp[n] << endl;
}