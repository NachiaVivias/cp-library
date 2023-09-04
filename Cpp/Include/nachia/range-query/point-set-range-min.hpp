#pragma once
#include "../array/segtree.hpp"
#include <functional>

namespace nachia {
    template<class S, class Cmp = std::less<S>>
    struct PointSetRangeMin{
    private:
        static S minop(S l, S r){ return std::min(l, r, Cmp()); }
        using Base = Segtree<S, minop>;
        Base base;
        Cmp cmpx;
    public:
        PointSetRangeMin() {}
        PointSetRangeMin(int len, S INF)
            : base(len, INF){}
        PointSetRangeMin(const std::vector<S>& init, S INF)
            : base(init, INF){}
        S min(int l, int r) const { return base.prod(l, r); }
        S min() const { return base.allProd(); }
        void set(int pos, S val){ base.set(pos, val); }
        S get(int pos) const { return base.get(pos); }
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
