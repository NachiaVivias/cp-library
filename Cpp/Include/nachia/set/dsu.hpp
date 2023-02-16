#pragma once
#include <vector>
#include <algorithm>

namespace nachia {

struct Dsu{
private:
    int N;
    std::vector<int> P;
    std::vector<int> H;
public:
    Dsu() : N(0) {}
    Dsu(int n) : N(n), P(n, -1), H(n) {
        for(int i=0; i<n; i++) H[i] = i;
    }
    int leader(int u){
        if(P[u] < 0) return u;
        int v = P[u];
        while(P[v] >= 0){ P[u] = P[v]; u = v; v = P[v]; }
        return P[u];
    }
    int append(){
        int n = P.size();
        P.push_back(-1);
        H.push_back(n);
        return n;
    }
    int label(int u){ return H[leader(u)]; }
    int operator[](int u){ return H[leader(u)]; }
    void merge(int u, int v, int newLabel){
        if(newLabel < 0) newLabel = u;
        u = leader(u);
        v = leader(v);
        if(u == v){ H[u] = newLabel; return; }
        N--;
        if(-P[u] < -P[v]) std::swap(u, v);
        P[u] += P[v];
        H[P[v] = u] = newLabel;
    }
    int merge(int u, int v){ merge(u, v, u); return u; }
    int count(){ return N; }
    int size(int u){ return -P[leader(u)]; }
    bool same(int u, int v){ return leader(u) == leader(v); }
};

} // namespace nachia
