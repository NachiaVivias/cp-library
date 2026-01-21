#pragma once
#include <vector>
#include <algorithm>

namespace nachia{

template<class Func, class Eval>
struct LiChaoTreeFlexible{
private:
    int xn;
    int N;
    std::vector<Func> V;
    std::vector<bool> visited;
    Func InfFunc;
    Eval ev;

    bool cmpat(Func fl, Func fr, int p){
        if(p >= xn) p = xn-1;
        return ev(fl, p) < ev(fr, p);
    }
public:
    
    LiChaoTreeFlexible(int n, Func inf, Eval eval)
        : xn(n)
        , InfFunc(std::move(inf))
        , ev(std::move(eval))
    {
        N = 1;
        while(N < n) N *= 2;
        V.assign(N*2, InfFunc);
        visited.assign(N*2, false);
    }
    
    void addSegment(int l, int r, Func f){
        if(l >= r) return;
        auto dfs = [&](int i,Func f,int a,int b,auto& dfs) -> void {
            visited[i] = true;
            if(i >= (int)V.size()) return;
            if(r <= a || b <= l) return;
            int m = (a+b)/2;
            if(!(l <= a && b <= r)){
                dfs(i*2,f,a,m,dfs);
                dfs(i*2+1,f,m,b,dfs);
                return;
            }
            if(cmpat(f, V[i], m)) std::swap(V[i],f);
            if(a + 1 == b) return;
            bool lessf_l = cmpat(f, V[i], a);
            bool lessf_r = cmpat(f, V[i], b-1);
            if(!lessf_l && !lessf_r) return;
            if(lessf_l) dfs(i*2,f,a,m,dfs);
            else dfs(i*2+1,f,m,b,dfs);
        };
        dfs(1,f,0,N,dfs);
    }
    
    void addLine(Func f){
        addSegment(0,N,f);
    }
    
    Func minFunc(int p){
        int i = 1;
        Func res = InfFunc;
        int l = 0, r = N;
        while(i < (int)V.size()){
            if(!visited[i]) break;
            if(cmpat(V[i], res, p)) res = V[i];
            int m = (l+r)/2;
            if(p < m){ i = i*2; r = m; }
            else{ i = i*2+1; l = m; }
        }
        return res;
    }
};

}
