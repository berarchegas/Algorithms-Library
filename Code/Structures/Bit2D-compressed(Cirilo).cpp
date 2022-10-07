// BIT 2D
//

struct bit2d{
    vector<int> x;
    vector<vector<int>> y, bit;
 
    bit2d(vector<pair<int,int>> p){
        sort(p.begin(),p.end());
 
        for(auto i : p){
            if(x.size() == 0 || x.back() != i.first)
                x.push_back(i.first);
        }
 
        bit.resize(x.size() + 1);
        y.resize(bit.size());
 
        for(auto &i : p){
            swap(i.first,i.second);
        }
 
        sort(p.begin(),p.end());
 
 
        for(auto &i : p){
            swap(i.first,i.second);
 
            for(int j = upper_bound(x.begin(),x.end(),i.first) - x.begin();j < bit.size();j += (j&-j)){
                if(y[j].size() == 0 || y[j].back() != i.second)
                    y[j].push_back(i.second);
            }
        }
    
        for(int i = 0;i < bit.size();i++){
            bit[i].resize(y[i].size() + 1,0);
        }
    }
 
    void up(pair<int,int> p,int novo){
        for(int i = upper_bound(x.begin(),x.end(),p.first) - x.begin();i < bit.size();i += (i&-i)){
            for(int j = upper_bound(y[i].begin(),y[i].end(),p.second) - y[i].begin();j < bit[i].size();j += (j&-j)){
                bit[i][j] += novo;
            }
        }
    }
 
    int get(pair<int,int> p){
        int res = 0;
        for(int i = upper_bound(x.begin(),x.end(),p.first) - x.begin();i > 0;i -= (i&-i)){
            for(int j = upper_bound(y[i].begin(),y[i].end(),p.second) - y[i].begin();j > 0;j -= (j&-j)){
                res += bit[i][j];
            }
        }
        return res;
    }
};