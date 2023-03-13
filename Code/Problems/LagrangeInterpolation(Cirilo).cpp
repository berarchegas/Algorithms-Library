#include<bits/stdc++.h>
 
using namespace std;
#define int long long
 
const int MAXN = 2001000;
const int mod = 1000000007;
 
int n,k;
int fat[MAXN], y[MAXN];
 
int powmod(int a,int b){
  int res = 1;
  while(b > 0){
    if(b % 2 == 0) a *= a, a %= mod, b /= 2;
    else res *= a, res %= mod, b --;
  }
 
  return res;
}
 
int inter(int x){
 
  for(int i = 1;i <= k + 2;i++){
    y[i] = y[i - 1] + powmod(i,k);
    y[i] %= mod;
  }
 
  
  if(x <= k + 2) return y[x];
  k += 2;
  
  int px = 1;
  fat[0] = 1;
  for(int i = 1;i <= k;i++){ 
    px *= i - x;
    px %= mod;
 
    fat[i] = fat[i - 1] * i;
    fat[i] %= mod;
  }
  
  int res = 0;
  for(int i = 1;i <= k;i++){
    int at = px * powmod(i - x,mod - 2);
    at %= mod;
    
    at *= y[i];
    at %= mod;

    at *= powmod(fat[k - i],mod-2);
    at %= mod;
    
    if(i % 2 == 0) at *= -powmod(fat[i - 1],mod-2);
    else at *= powmod(fat[i - 1],mod-2);
    at %= mod;
 
    res += at;
    res %= mod;
  }
 
  return res;
}
 
signed main(){
  cin >> n >> k;
 
  cout << (inter(n) + mod) % mod << endl;
}