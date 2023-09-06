#pragma once
#include "../array/lazy-segtree.hpp"
#include <functional>

namespace nachia {
    template<class S, class Cmp = std::less<S>>
    struct RangeAddRangeMin{
    private:
        static S minop(S l, S r){ return std::min(l, r, Cmp()); }
        static S addop(S f, S x){ return f + x; }
        using Base = LazySegtree<S, S, minop, addop, addop>;
        Base base;
        Cmp cmpx;
    public:
        RangeAddRangeMin() {}
        RangeAddRangeMin(int len, S INF, S ZERO)
            : base(len, INF, ZERO){}
        RangeAddRangeMin(const std::vector<S>& init, S INF, S ZERO)
            : base(init, INF, ZERO){}
        S min(int l, int r){ return base.prod(l, r); }
        S min(){ return base.allProd(); }
        void add(int l, int r, S val){ base.apply(l, r, val); }
        void add(int p, S val){ base.apply(p, val); }
        void set(int p, S val){ base.set(p, val); }
        S get(int p){ return base.get(p); }
        int lBoundLeft(int from, S val){ return base.minLeft(from, [this,val](const S& x){ return cmpx(val, x); }); }
        int uBoundLeft(int from, S val){ return base.minLeft(from, [this,val](const S& x){ return !cmpx(x, val); }); }
        int lBoundRight(int from, S val){ return base.maxRight(from, [this,val](const S& x){ return cmpx(val, x); }); }
        int uBoundRight(int from, S val){ return base.maxRight(from, [this,val](const S& x){ return !cmpx(x, val); }); }
        template<class E>
        int minLeft(int r, E cmp){ return base.minLeft(r, cmp); }
        template<class E>
        int maxRight(int l, E cmp){ return base.maxRight(l, cmp); }
    };
} // namespace nachia
