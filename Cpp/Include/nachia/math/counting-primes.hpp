#pragma once
#include <vector>
#include <utility>
#include "../math/floor-of-kth-root.hpp"
#include "../bit/bit-operations.hpp"

namespace nachia{

std::pair<std::vector<long long>, std::vector<long long>>
    CountingPrimesTable(long long maxval)
{
    struct Div2By1 {
        using u32 = unsigned int;
        using u64 = unsigned long long;
        int w;
        u32 d;
        u32 v;
        Div2By1(){}
        Div2By1(u32 m){
            w = 31 - MsbIndex(m);
            d = m << w;
            v = (u32)((u64(-1) / d) - (u64(1) << 32));
        }
        u32 operator()(u64 u) const {
            u <<= w;
            u32 u1 = u32(u >> 32);
            u32 q = u32((u64(1) * v * u1) >> 32) + u1;
            u -= u64(1) * q * d;
            if (u >= u64(2) * d){ u -= u64(2) * d; q += 2; }
            if (u >= d){ q += 1; }
            return q;
        }
    };
    using i64 = long long;
    i64 N = maxval;
    if(N <= 1) return { {0,0}, {0,0} };

    i64 Nr2 = FloorOfKthRoot(N, 2);
    i64 Nr4 = FloorOfKthRoot(Nr2, 2);
    i64 Dsz = N / (Nr2+1);
    i64 Asz = (Nr2+1) + Dsz;
    
    std::vector<i64> Div(Nr2+1);
    for(i64 i=1; i<=Nr2; i++) Div[i] = N / i;
    
    std::vector<i64> A(Asz + 1, 0);

    for(i64 i=1; i<=Nr2; i++) A[i] = i-1;
    for(i64 i=1; i<=Dsz; i++) A[Asz-i] = Div[i]-1;

    for(i64 p=2; p<=Nr4; p++) if(A[p] - A[p-1] != 0){
        auto div2By1 = Div2By1(p);
        i64 i = 1;
        i64 small = A[p-1];
        for( ; i*p<=Dsz; i++) A[Asz-i] -= A[Asz-i*p] - small;
        for( ; i<=Dsz; i++) A[Asz-i] -= A[div2By1(Div[i])] - small;
        i64 Nr2dp = div2By1(Nr2);
        for(i64 j=Nr2dp*p; j<=Nr2; j++) A[j] -= A[Nr2dp] - small;
        for(i64 j=Nr2dp-1; j>=p; j--) for(i64 t=0; t<p; t++) A[j*p+t] -= A[j] - small;
    }
    
    for(i64 p=Nr4+1; p<=Nr2; p++) if(A[p] - A[p-1] != 0){
        auto div2By1 = Div2By1(p);
        i64 i = 1;
        i64 small = A[p-1];
        i64 l = div2By1(Div[p]);
        for( ; i*p<=Dsz; i++) A[Asz-i] -= A[Asz-i*p] - small;
        for( ; i<=l; i++) A[Asz-i] -= A[div2By1(Div[i])] - small;
    }
    
    return std::make_pair(
        std::vector<i64>(A.begin(), A.begin() + (Nr2 + 1)),
        std::vector<i64>(A.rbegin(), A.rbegin() + (Dsz + 1))
    );
}

long long CountingPrimes(long long maxval){
    return CountingPrimesTable(maxval).second[1];
}

} // namespace nachia
