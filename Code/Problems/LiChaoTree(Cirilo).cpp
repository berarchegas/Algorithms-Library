// Li Chao Tree
//
#include<bits/stdc++.h>
    
using namespace std;
const int MAXN = 100100;
    
#define int long long
const long long INF = 0x3f3f3f3f;
    
pair<long long,long long> linf = {INF,INF*INF};
    
struct lct{
    lct *fe,*fd;
    int l,r,meio;
    pair<long long,long long> p;
    
    lct(int x,int y){
        l = x,r = y;
        meio = (x + y) / 2;
        if(meio == y && x != y) meio --;
    
        p = linf;
        fe = fd = NULL;
    }
    
    pair<pair<int,int>,int> comp(pair<int,int> k1,pair<int,int> k2){
        if(k1.first < k2.first) swap(k1,k2);
    
        if(k1.first * meio + k1.second <= k2.first * meio + k2.second){
            p = k1;
            return {k2,1};
        }
    
        p = k2;
        return {k1,0};
    }
    
    pair<int,int> minx(pair<int,int> k,int x){
        if(k.first * x + k.second <= p.first * x + p.second) return k;
        return p;
    }
    
    int res(pair<int,int> k,int x){
        return k.first * x + k.second;
    }
    
    void up(pair<int,int> ll){
        pair<pair<int,int>,int> k = comp(ll,p);
    
        if(l == r) return;
    
        if(k.second == 0){
            if(fe == NULL) fe = new lct(l,meio);
            fe->up(k.first);
        }
        else{
            if(fd == NULL) fd = new lct(meio + 1,r);
            fd->up(k.first);
        }
    }
    
    int get(pair<int,int> ll,int x){
        ll = minx(ll,x);
        if(l == r) return res(ll,x);
        if(x <= meio){
            if(fe == NULL) return res(ll,x);
            return fe->get(ll,x);
        } 
        else{
            if(fd == NULL) return res(ll,x);
            return fd->get(ll,x);
        }
    }
    
    ~lct(){
        if(fe != NULL) delete fe;
        if(fd != NULL) delete fd;
    }
};
    
int a[MAXN] , b[MAXN];
vector<pair<int,int>> vec[MAXN];
vector<int> grafo[MAXN];
long long p[MAXN],res[MAXN];
bool vis[MAXN];
lct *tree[MAXN];
    
void dfs(int x){
    vis[x] = true;
    
    pair<int,int> mex = {0,0};
    for(auto i : grafo[x]){
        if(vis[i] == true) continue;
        dfs(i);
    
        if(vec[p[i]].size() > mex.first) mex = {vec[p[i]].size(),p[i]};
    }
    
    if(mex.first == 0) p[x] = x;
    else p[x] = mex.second;
    
    if(mex.second == 0) tree[x] = new lct(-MAXN,MAXN);
    else tree[x] = tree[mex.second];
    
    for(auto i : grafo[x]){
        if(p[i] == mex.second) continue;
    
        for(auto j : vec[p[i]]){
            tree[x]->up(j);
            vec[p[x]].push_back(j);
        }
    
        delete tree[p[i]];
    }
    
    if(mex.second != 0) res[x] = tree[x]->get(linf,a[x]);
    
    tree[x]->up({b[x],res[x]});
    vec[p[x]].push_back({b[x],res[x]});
}
    
signed main(){
    int n;
    cin >> n;
    
    for(int i = 1;i <= n;i++) cin >> a[i];
    for(int i = 1;i <= n;i++) cin >> b[i];
    
    for(int i = 1;i < n;i++){
        int x,y;
        cin >> x >> y;
        grafo[x].push_back(y);
        grafo[y].push_back(x);
    }
    
    dfs(1);
    
    for(int i = 1;i <= n;i++) cout << res[i] << " ";
    cout << endl;
}