// Divide and Conquer Optmization
//
#include<bits/stdc++.h>
    
using namespace std;
const int MAXN = 4010;
const int INF = 0x3f3f3f3f;
    
int v[MAXN][MAXN];
int c[MAXN][MAXN];
int s[MAXN][MAXN];
int memo[1000][MAXN];
int aux[MAXN];
    
void divide_opt(int l,int r,int optl,int optr,int it){
    int meio = (r + l) / 2;
    
    if(l > r) return;
    
    pair<int,int> best = {INF,-1};
    for(int i = optl;i <= min(optr,meio);i++){
        best = min(best,{memo[it - 1][i] + c[meio][i + 1],i});
    }
    
    memo[it][meio] = best.first;
    if(l == r) return;
    
    divide_opt(l,meio - 1,optl,best.second,it);
    divide_opt(meio + 1,r,best.second,optr,it);
}	
    
int read()
{
    int ret = 0;
    char c;
    while(!isdigit(c = getchar()));
    ret += c - '0';
    while(isdigit(c = getchar()))
        ret = 10 * ret + c - '0';
    return ret;
}
    
int main(){
    ios_base::sync_with_stdio(false), cin.tie(0);
    
    int n,k;
    n = read() , k = read();
    
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= n;j++){
            s[i][j] = s[i][j - 1]; 
            v[i][j] = read();
    
            s[i][j] += v[i][j];
        }
    
    for(int i = 1;i <= n;i++){
        for(int j = 1;j < i;j++){
            c[i][j] = c[i - 1][j] + s[i][i] - s[i][j - 1];
        }
    }
    
    memset(memo,INF,sizeof memo);
    memo[0][0] = 0;
    for(int i = 1;i <= k;i++){
        divide_opt(1,n,0,n,i);
    }
    
    printf("%d\n",memo[k][n]);
}