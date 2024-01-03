#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include "../unit-lib.hpp"

/*

verifier for binary search function of

* segment tree
* lazy segment tree

Problem : Range sum of array of (1,1,1, ... )

*/

#include "../../../Include/nachia/array/segtree.hpp"
#include <cassert>
#include <algorithm>

int AddInt(int l, int r){ return l + r; }

void solve(nachia::Xoshiro256pp& rng){
    int N = rng.random_unsigned(100, 300);

    auto ds = nachia::Segtree<int, AddInt>(N, 0);
    for(int i=0; i<=N; i++){
        for(int j=0; j<=N+1; j++){
            int f = ds.minLeft(i, [&](int x){ return x <= j; });
            int expect = std::max<int>(0, i-j);
            assert(f == expect);
        }
    }
    for(int i=0; i<=N; i++){
        for(int j=0; j<=N+1; j++){
            int f = ds.maxRight(i, [&](int x){ return x <= j; });
            int expect = std::min<int>(N, i+j);
            assert(f == expect);
        }
    }
}
