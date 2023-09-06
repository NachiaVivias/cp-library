#pragma once
#include <vector>

namespace nachia{

template<
    class S,
    S op(S l, S r)
>
struct Segtree {
private:
    int N;
    std::vector<S> A;

    void mergev(int i){
        if(i < N) A[i] = op(A[i*2], A[i*2+1]);
    }
public:
    Segtree() : N(0) {}
    Segtree(int n, S e){
        N = 1; while (N < n) N *= 2;
        A.assign(N * 2, e);
    }
    Segtree(const std::vector<S>& a, S e) : Segtree(a.size(), e){
        for(int i=0; i<(int)a.size(); i++) A[i + N] = a[i];
        for(int i=N-1; i>=1; i--) mergev(i);
    }

    void set(int p, S x){
        p += N; A[p] = x;
        for(int d=1; (1<<d)<=N; d++) mergev(p>>d);
    }

    S get(int p) const { return A[N+p]; }

    S prod(int l, int r) const {
        l += N; r += N;
        S ql = A[0], qr = A[0];
        while(l<r){
            if(l&1) ql = op(ql, A[l++]);
            if(r&1) qr = op(A[--r], qr);
            l /= 2;
            r /= 2;
        }
        return op(ql, qr);
    }

    S allProd() const { return A[1]; }

    // bool cmp(S)
    template<class E>
    int minLeft(int r, E cmp, int a = 0, int b = 0, int i = -1){
        static S x;
        if(i == -1){ a=0; b=N; i=1; x=A[0]; }
        if(r <= a) return a;
        if(b <= r){
            S nx = op(A[i], x);
            if(cmp(nx)){ x = nx; return a; }
        }
        if(b - a == 1) return b;
        int q = minLeft(r, cmp, (a+b)/2, b, i*2+1);
        if(q > (a+b)/2) return q;
        return minLeft(r, cmp, a, (a+b)/2, i*2);
    }

    // bool cmp(S)
    template<class E>
    int maxRight(int l, E cmp, int a = 0, int b = 0, int i = -1){
        static S x;
        if(i == -1){ a=0; b=N; i=1; x=A[0]; }
        if(b <= l) return b;
        if(l <= a){
            S nx = op(x, A[i]);
            if(cmp(nx)){ x = nx; return b; }
        }
        if(b - a == 1) return a;
        int q = maxRight(l, cmp, a, (a+b)/2, i*2);
        if(q < (a+b)/2) return q;
        return maxRight(l, cmp, (a+b)/2, b, i*2+1);
    }
};

} // namespace nachia
