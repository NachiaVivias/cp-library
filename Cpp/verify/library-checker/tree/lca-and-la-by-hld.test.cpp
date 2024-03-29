#define PROBLEM "https://judge.yosupo.jp/problem/lca"
#include "../../../Include/nachia/tree/heavy-light-decomposition.hpp"
#include "../../../Include/nachia/misc/fastio.hpp"
#include <vector>
#include <algorithm>
#include <cassert>
#include <cstdint>


class Randomizer_NV{
public:
    using i32 = int32_t;
    using u32 = uint32_t;
    using i64 = int64_t;
    using u64 = uint64_t;
private:

    u32 rngx = 1234567890;
    u32 rngy = 987654321;
    u32 rngz = 998244353;
    u32 rngw = 1000000007;

public:

    void seed(u32 x = 1234567890, u32 y = 987654321, u32 z = 998244353, u32 w = 1000000007){
        rngx = x;
        rngy = y;
        rngz = z;
        rngw = w;
    }

    u32 rng32() {
        const u32 t = rngx ^ (rngx << 11);
        rngx = rngy; rngy = rngz; rngz = rngw;
        return rngw = rngw ^ (rngw >> 19) ^ t ^ (t >> 8);
    }
    u64 rng64() {
        return (u64)rng32() << 32 | rng32();
    }

    // generate x : l <= x <= r
    u64 random_unsigned(u64 l,u64 r){
        assert(l<=r);
        r-=l;
        auto res = rng64();
        if(res<=r) return res+l;
        u64 d = r+1;
        u64 max_valid = 0xffffffffffffffff/d*d;
        while(true){
            auto res = rng64();
            if(res<=max_valid) break;
        }
        return res%d+l;
    }


};

int main() {
    using nachia::cin;
    using nachia::cout;

    Randomizer_NV rng;

    int N = cin.nextU32();
    int Q = cin.nextU32();
    std::vector<std::pair<int,int>> edges(N-1);
    for(int i=1; i<N; i++){
        int p = cin.nextU32();
        edges[i-1] = { p, i };
    }

    auto hld = nachia::HeavyLightDecomposition(nachia::CsrArray<int>::Construct(N, edges));

    for(int i=0; i<Q; i++){
        int u = cin.nextU32();
        int v = cin.nextU32();
        int g = hld.lca(u, v);
        int d = hld.depth(u) + hld.depth(v) - hld.depth(g) * 2;
        int la_d = (int)rng.random_unsigned(0, d+2) - 1;
        int la_res = hld.la(u, v, la_d);
        if(la_d < 0 || d < la_d){
            if(la_res != -1){ cout << "-1\n"; exit(0); }
        }
        else{
            if(la_res == -1){ cout << "-1\n"; exit(0); }
            if(hld.dist(u, la_res) != la_d){ cout << "-1\n"; exit(0); }
            if(la_d + hld.dist(la_res, v) != d){ cout << "-1\n"; exit(0); }
        }
        cout << g << '\n';
    }
    return 0;
}
