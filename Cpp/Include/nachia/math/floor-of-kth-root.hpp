#pragma once

#include <cassert>

namespace nachia{

namespace internal{

// mod 2^64
constexpr unsigned long long PowerOfULongLong(unsigned long long a, unsigned long long i){
    unsigned long long res = 1;
    while(i){ if(i&1){ res *= a; } i /= 2; a *= a; }
    return res;
}

}

unsigned long long FloorOfKthRoot(unsigned long long real, unsigned long long k){
    using u64 = unsigned long long;
    assert(k != 0);
    if(real <= 1) return real;
    if(k >= 64) return 1;
    if(k == 1) return real;
    struct Precalc{
        // a^i <= x
        static constexpr bool lesseq(u64 a, int i, u64 x) {
            if (a == 0) return true;
            for(int j=0; j<i; j++) x /= a;
            return x >= 1;
        }
        unsigned long long BORDER[64];
        constexpr Precalc() : BORDER() {
            for (int idx = 2; idx <= 63; idx++) {
                u64 l = 0, r = 1ull << 33;
                while (l + 1 < r) {
                    u64 m = (l + r) / 2;
                    if (lesseq(m, idx, ~0ull)) l = m;
                    else r = m;
                }
                BORDER[idx] = r;
            }
        };
    };
    constexpr Precalc precalc;
    u64 l = 0, r = precalc.BORDER[k];
    if(real < r) r = real;
    while (l + 1 < r) {
        u64 m = (l + r) / 2;
        if(internal::PowerOfULongLong(m, k) <= real) l = m;
        else r = m;
    }
    return l;
}

unsigned long long CeilOfKthRoot(unsigned long long real, unsigned long long k){
    if(real <= 1) return real;
    if(k >= 64) return 2;
    if(k == 1) return real;
    unsigned long long x = FloorOfKthRoot(real, k);
    if(internal::PowerOfULongLong(x, k) != real) x++;
    return x;
}

} // namespace nachia
