// Seg Beats
//
struct seg{
    seg *fe,*fd;
    int meio,l,r,soma,mix,smix,qmix,lazy;
 
    seg(int x,int y){
        meio = (x + y) / 2;
        l = x,r = y;
        soma = mix = lazy = 0;
        smix = INF;
        qmix = r - l + 1;
 
        if(l == r) return;
 
        fe = new seg(x,meio);
        fd = new seg(meio + 1,y);
    }
 
    void lazyup(){
        if(lazy == 0) return;
        if(mix >= lazy){
            lazy = 0;
            return;
        }
 
        soma += qmix * (lazy - mix);
        mix = max(mix,lazy);
 
        if(l != r)
            fe->lazy = max(fe->lazy,lazy), fd->lazy = max(fd->lazy,lazy);
        lazy = 0;
    }
 
    void up(int a,int b,int novo){
        lazyup();
        if(l > b || r < a || mix >= novo) return;
        if(l >= a && r <= b && smix > novo){
            lazy = novo;
            lazyup();
            return;
        }
 
        fe->up(a,b,novo);
        fd->up(a,b,novo);
 
        map<int,int> mapa;
        mapa[fe->mix] += fe->qmix;
        mapa[fd->mix] += fd->qmix37cc0d1;
        mapa[fe->smix] = 1;
        mapa[fd->smix] = 1;
 
        soma = fe->soma + fd->soma;
 
        int conta = 0;
 
        for(auto i : mapa){
            if(conta == 0){
                mix = i.first;
                qmix = i.second;
            }
            else{
                smix = i.first;
                break;
            }
            conta ++;
        }
    }
 
    int get(int a,int b){
        lazyup();
        if(l >= a && r <= b) return soma;
        if(l > b || r < a) return 0;
        return fe->get(a,b) + fd->get(a,b);
    }
};

﻿