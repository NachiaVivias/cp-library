#pragma once
#include <vector>
#include "../misc/bit-operations.hpp"
#include "../set/dsu-fast.hpp"

namespace nachia {

struct DecrementalPredecessorQuery{
private:
    int n;
    int b;
    std::vector<unsigned long long> X;
    nachia::DsuFast Y;
    std::vector<int> dsuTrans;
    int smallQ(int c, int d) const noexcept {
        auto z = X[c] & ((~0ull) << d);
        return z ? c*64 + LsbIndex(z) : -1;
    }
    int largeQ(int c) noexcept { return dsuTrans[Y.leader(c)]; }
public:
    DecrementalPredecessorQuery(int _n)
        : n(_n+2), b(n/64+2), X(b, ~0ull), Y(b), dsuTrans(b)
    {
        for(int i=0; i<b; i++) dsuTrans[i] = i;
    }
    // remove token p
    void dec(int p){
        p++;
        int c = p/64, d = p%64;
        X[c] &= ~(1ull << d);
        if(X[c] == 0){
            int h = largeQ(c+1);
            dsuTrans[Y.merge(c, c+1)] = h;
        }
    }
    // minimum token left p : x <= p
    int queryNoLessThan(int x){
        x++;
        int c = x/64, d = x%64;
        int p = smallQ(c, d);
        if(p >= 0) return p-1;
        c = largeQ(c+1); d = 0;
        return smallQ(c, d)-1;
    }
};

} // namespace nachia
