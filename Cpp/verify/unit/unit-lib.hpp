#pragma once
#include <cstdio>

#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cassert>
#include <cstdint>


namespace nachia{

class Xoshiro256pp{
public:

    using i32 = int32_t;
    using u32 = uint32_t;
    using i64 = int64_t;
    using u64 = uint64_t;


private:
    uint64_t s[4];

    // https://prng.di.unimi.it/xoshiro256plusplus.c
    static inline uint64_t rotl(const uint64_t x, int k) noexcept {
        return (x << k) | (x >> (64 - k));
    }
    inline uint64_t next(void) noexcept {
        const uint64_t result = rotl(s[0] + s[3], 23) + s[0];
        const uint64_t t = s[1] << 17;
        s[2] ^= s[0];
        s[3] ^= s[1];
        s[1] ^= s[2];
        s[0] ^= s[3];
        s[2] ^= t;
        s[3] = rotl(s[3], 45);
        return result;
    }

    // https://xoshiro.di.unimi.it/splitmix64.c
    u64 splitmix64(u64& x) {
        u64 z = (x += 0x9e3779b97f4a7c15);
        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
        z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
        return z ^ (z >> 31);
    }

public:

    void seed(u64 x = 7001){
        assert(x != 0);
        s[0] = x;
        for(int i=1; i<4; i++) s[i] = splitmix64(x);
    }

    Xoshiro256pp(){ seed(); }
    
    u64 rng64() {
        return next();
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

    // generate x : l <= x <= r
    i64 random_signed(i64 l,i64 r){
        assert(l<=r);
        u64 unsigned_l = (u64)l ^ (1ull<<63);
        u64 unsigned_r = (u64)r ^ (1ull<<63);
        u64 unsigned_res = random_unsigned(unsigned_l,unsigned_r) ^ (1ull<<63);
        return (i64)unsigned_res;
    }


    // permute x : n_left <= x <= n_right
    // output r from the front
    template<class Int>
    std::vector<Int> random_nPr(Int n_left, Int n_right, Int r){
        Int n = n_right-n_left;

        assert(n>=0);
        assert(r<=(1ll<<27));
        if(r==0) return {};  
        assert(n>=r-1);

        if(n==0) return {};
        std::vector<Int> V;
        std::unordered_map<Int,Int> G;
        for(int i=0; i<r; i++){
            Int p = random_signed(i,n);
            Int x = p - G[p];
            V.push_back(x);
            G[p] = p - (i - G[i]);
        }

        for(Int& v : V) v+=n_left;
        return V;
    }



    // V[i] := V[perm[i]]
    // using swap
    template<class E,class PermInt_t>
    void permute_inplace(std::vector<E>& V,std::vector<PermInt_t> perm){
        assert(V.size() == perm.size());
        int N=V.size();
        for(int i=0; i<N; i++){
            int p=i;
            while(perm[p]!=i){
                assert(0 <= perm[p] && perm[p] < N);
                assert(perm[p] != perm[perm[p]]);
                std::swap(V[p],V[perm[p]]);
                int pbuf = perm[p]; perm[p] = p; p = pbuf;
            }
            perm[p] = p;
        }
    }

    template<class E>
    std::vector<E> shuffle(const std::vector<E>& V){
        int N=V.size();
        auto P = random_nPr(0,N-1,N);
        std::vector<E> res;
        res.reserve(N);
        for(int i=0; i<N; i++) res.push_back(V[P[i]]);
        return res;
    }

    // shuffle using swap
    template<class E>
    void shuffle_inplace(std::vector<E>& V){
        int N=V.size();
        permute_inplace(V,random_nPr(0,N-1,N));
    }


};

} // namespace nachia

void solve(nachia::Xoshiro256pp& rng);

int main(){
    nachia::Xoshiro256pp rng;
    long long a, b;
    scanf("%lld %lld", &a, &b);
    rng.seed((unsigned long long)(a + b));
    solve(rng);
    printf("%lld\n", a + b);
    return 0;
}
