#pragma once
#include <vector>

namespace nachia{

template<
    class S,
    class F,
    S op(S l, S r),
    F composition(F f, F x),
    S mapping(F f, S x)
>
struct LazySegtree {

    struct Node { S s; F f; bool propagated; };
    int N;
    int logN;
    std::vector<Node> A;

    void mapf(Node& a, F f){
        a.propagated = false;
        a.f = composition(f, a.f);
        a.s = mapping(f, a.s);
    }
    void mergev(int i){
        if(i<N) A[i].s = op(A[i*2].s, A[i*2+1].s);
    }
    void spread(int i){
        if(A[i].propagated || !(i < N)) return;
        mapf(A[i*2], A[i].f);
        mapf(A[i*2+1], A[i].f);
        A[i].f = A[0].f;
        A[i].propagated = true;
    }

    LazySegtree() : N(0), logN(-1){}
    LazySegtree(int n, S e, F id){
        N=1; logN=0;
        while(N<n){ N *= 2; logN++; }
        A.assign(N*2, { e, id, true });
    }
    LazySegtree(const std::vector<S>& a, S e, F id) : LazySegtree(a.size(), std::move(e), std::move(id)){
        for(std::size_t i=0; i<a.size(); i++) A[i+N].s = a[i];
        for(int i=N-1; i>=1; i--) mergev(i);
    }

    void set(int p, S x){
        p += N;
        for(int d=logN; d; d--) spread(p >> d);
        A[p].s = x;
        for(int d=1; d<=logN; d++) mergev(p >> d);
    }
    S get(int p){
        p += N;
        for(int d=logN; d; d--) spread(p >> d);
        return A[p].s;
    }
    void apply(int p, F f){ set(p, mapping(f, get(p))); }
    void apply(int l, int r, F f){
        if(!(l < r)) return;
        if(l == 0 && r == N){ mapf(A[1], f); return; }
        l += N; r += N;
        for(int d=logN; d; d--){
            if((l >> d) << d != l) spread(l >> d);
            if((r >> d) << d != r) spread(r >> d);
        }
        int lp = l, rp = r;
        while(l < r){
            if(l&1){ mapf(A[l++], f); } l /= 2;
            if(r&1){ mapf(A[--r], f); } r /= 2;
        }
        for(int d=1 ; d<=logN; d++){
            if((lp >> d) << d != lp) mergev(lp >> d);
            if((rp >> d) << d != rp) mergev(rp >> d);
        }
    }
    S prod(int l, int r){
        if(!(l < r)) return A[0].s;
        l += N; r += N;
        for(int d=logN; d; d--){
            if((l >> d) << d != l) spread(l >> d);
            if((r >> d) << d != r) spread(r >> d);
        }
        S q1 = A[0].s, q2 = A[0].s;
        while(l < r){
            if(l&1){ q1 = op(q1, A[l++].s); } l /= 2;
            if(r&1){ q2 = op(A[--r].s, q2); } r /= 2;
        }
        return op(q1, q2);
    }
    S allProd() const { return A[1].s; }
    // bool cmp(S)
    template<class E>
    int minLeft(int r, E cmp, int a = 0, int b = 0, int i = -1){
        static S x;
        if(i == -1){ a=0; b=N; i=1; x = A[0].s; }
        if(r <= a) return a;
        if(b <= r){
            S nx = op(A[i].s, x);
            if(cmp(nx)){ x = nx; return a; }
        }
        if(b - a == 1) return b;
        spread(i);
        int q = minLeft(r, cmp, (a+b)/2, b, i*2+1);
        if(q > (a+b)/2) return q;
        return minLeft(r, cmp, a, (a+b)/2, i*2);
    }
    // bool cmp(S)
    template<class E>
    int maxRight(int l, E cmp, int a = 0, int b = 0, int i = -1){
        static S x;
        if(i == -1){ a=0; b=N; i=1; x = A[0].s; }
        if(b <= l) return b;
        if(l <= a){
            S nx = op(x, A[i].s);
            if(cmp(nx)){ x = nx; return b; }
        }
        if(b - a == 1) return a;
        spread(i);
        int q = maxRight(l, cmp, a, (a+b)/2, i*2);
        if(q < (a+b)/2) return q;
        return maxRight(l, cmp, (a+b)/2, b, i*2+1);
    }
};

} // namespace nachia;
