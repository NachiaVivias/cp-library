#pragma once
#include <vector>
#include <algorithm>
#include <functional>

namespace nachia {

template<class Elem = long long, class Freq = long long, class Compare = std::less<Elem>>
struct RangeAddCountTopK {
public:
    struct Node { Elem x; Freq f; };
private:
    int N = 0;
    int K = 0;
    Compare Cmp;
    std::vector<Node> A;
    std::vector<Elem> de;
    using Iter = typename std::vector<Node>::iterator;
    void mergeK(int K, Iter r, Iter i, Iter j){
        for(int k=0; k<K; k++){
            if(Cmp(j->x, i->x)){ *r = *i; i++; }
            else if(Cmp(i->x, j->x)){ *r = *j; j++; }
            else { *r = *i; r->f += j->f; i++; j++; }
            r++;
        }
    }
    static int shiN(int n){ int f=1; while(f<n){ f*=2; } return f; }
    auto beginAt(int p){ return A.begin() + (p*K); }
    auto beginAt(int p) const { return A.begin() + (p*K); }
    void addAt(int p, Elem x){
        auto a = beginAt(p);
        Elem Min = A[0].x;
        for(int k=0; k<K && Cmp(Min, a[k].x); k++) a[k].x += x;
        if(p < N){
            if(Cmp(Min, de[p])) de[p] += x; else de[p] = x;
        }
    }
    void propagate(int p){
        Elem Min = A[0].x;
        if(!Cmp(Min, de[p])) return;
        addAt(p*2, de[p]); addAt(p*2+1, de[p]);
        de[p] = Min;
    }
    void aggregate(int p){
        mergeK(K, beginAt(p), beginAt(p*2), beginAt(p*2+1));
    }
    void rangeAdd2(int l, int r, Elem x, int i, int a, int b){
        if(r <= a || b <= l) return;
        if(l <= a && b <= r){ addAt(i, x); return; }
        propagate(i);
        rangeAdd2(l, r, x, i*2, a, (a+b)/2);
        rangeAdd2(l, r, x, i*2+1, (a+b)/2, b);
        aggregate(i);
    }
    void rangeTopK2(int l, int r, Iter x, Iter y, int i, int a, int b){
        if(r <= a || b <= l) return;
        if(l <= a && b <= r){
            for(int k=0; k<K; k++) y[k] = x[k];
            mergeK(K, x, y, beginAt(i));
            return;
        }
        propagate(i);
        rangeTopK2(l, r, x, y, i*2, a, (a+b)/2);
        rangeTopK2(l, r, x, y, i*2+1, (a+b)/2, b);
        aggregate(i);
    }
public:
    RangeAddCountTopK(Compare cmp = Compare()) : N(0), K(0), Cmp(cmp) {}
    RangeAddCountTopK(
        int n, int k,
        Elem fillV, Freq fillF,
        Elem Min, Freq fZero = Freq(0),
        Compare cmp = Compare()
    ) :
        N(shiN(n)), K(k), Cmp(cmp),
        A(N*2*K+1, { Min, fZero }),
        de(N, Min) {
        for(int i=0; i<n; i++) A[(N+i)*K] = {fillV,fillF};
        for(int i=N-1; i>=1; i--) aggregate(i);
    }
    void rangeAdd(int l, int r, Elem x){ rangeAdd2(l,r,x,1,0,N); }
    std::vector<Node> topK() const {
        auto i = beginAt(1);
        return std::vector<Node>(i, i+K);
    }
    std::vector<Node> rangeTopK(int l, int r){
        std::vector<Node> q0(beginAt(0), beginAt(1));
        std::vector<Node> q1(beginAt(0), beginAt(1));
        rangeTopK2(l,r,q0.begin(),q1.begin(),1,0,N);
        return q0;
    }
};

} // namespace nachia
