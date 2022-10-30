#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det"
#include "../../../Include/nachia/linear/matrix-modulo.hpp"
#include "../../../Include/nachia/misc/fastio.hpp"
using u32 = unsigned int;
using u64 = unsigned long long;



template<u32 MOD>
struct LazyMontgomeryModint{
private:
    static constexpr u32 get_ninv(){
        u32 res = 0;
        u32 t = 0;
        for(u32 d=0; d<32; d++){
            if(!(t & 1)){ t += MOD; res |= (u32)1 << d; }
            t >>= 1;
        }
        return res;
    }
    static constexpr u32 get_r2(){
        u64 r2 = ((u64)1 << 32) % MOD; r2 = (u64)r2 * r2 % MOD;
        return r2;
    }
    static u32 montgomery_reduction(u64 t){
        u32 ninv = get_ninv();
        t = (t + (u64)(u32)((u32)t * ninv) * MOD) >> 32;
        if(t >= MOD) t -= MOD;
        return t;
    }

    u32 x;
public:

    using my_type = LazyMontgomeryModint;

    LazyMontgomeryModint() : x(0){}
    LazyMontgomeryModint(u32 v) : x(montgomery_reduction((u64)v * get_r2())){}
    u32 operator*() const { return montgomery_reduction(x); }
    my_type& operator+=(const my_type& r){ x += r.x; if(x >= MOD) x -= MOD; return *this; }
    my_type operator+(const my_type& r) const { my_type res = *this; return res += r; }
    my_type& operator-=(const my_type& r){ x += MOD - r.x; if(x >= MOD) x -= MOD; return *this; }
    my_type operator-(const my_type& r) const { my_type res = *this; return res -= r; }
    my_type operator-() const { my_type res = *this; res.x = ((res.x == 0) ? 0 : (MOD - res.x)); return res; }
    my_type& operator*=(const my_type& r){ x = montgomery_reduction((u64)x * r.x); return *this; }
    my_type operator*(const my_type& r) const { my_type res = *this; return res *= r; }
    my_type pow(u64 i) const {
        my_type a = *this, res = 1;
        while(i){ if(i & 1) res *= a; a *= a; i >>= 1; }
        return res;
    }
    my_type inv() const { return pow(MOD-2); }
    u32 val() const { return **this; }
    static u32 get_mod() { return MOD; }
};


int main() {
    int N = nachia::cin.nextU32();
    const unsigned int MOD = 998244353;
    nachia::MatrixModulo<LazyMontgomeryModint<998244353>> A(N, N);
    for(int y=0; y<N; y++) for(int x=0; x<N; x++) A[y][x] = nachia::cin.nextU32();
    unsigned int ans = *A.det();
    nachia::cout << ans << "\n";
    return 0;
}
