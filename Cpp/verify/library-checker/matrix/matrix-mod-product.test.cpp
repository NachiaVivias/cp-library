#define PROBLEM "https://judge.yosupo.jp/problem/matrix_product"
#include "../../../Include/nachia/linear-modulo/matrix-modulo.hpp"
#include "../../../Include/nachia/misc/fastio.hpp"


namespace nachia_verify{

using u32 = unsigned int;
using u64 = unsigned long long;



template<u32 MOD>
struct Modint{
private:
    u32 x;
public:

    using my_type = Modint;

    Modint() : x(0){}
    Modint(u32 v) : x(v){}
    u32 operator*() const { return x; }
    my_type& operator+=(const my_type& r){ u32 t = x + r.x; if(t >= MOD) t -= MOD; x = t; return *this; }
    my_type operator+(const my_type& r) const { my_type res = *this; return res += r; }
    my_type& operator-=(const my_type& r){ u32 t = x + MOD - r.x; if(t >= MOD) t -= MOD; x = t; return *this; }
    my_type operator-(const my_type& r) const { my_type res = *this; return res -= r; }
    my_type operator-() const { my_type res = *this; res.x = ((res.x == 0) ? 0 : (MOD - res.x)); return res; }
    my_type& operator*=(const my_type& r){ x = (u64)x * r.x % MOD; return *this; }
    my_type operator*(const my_type& r) const { my_type res = *this; return res *= r; }
    my_type pow(u64 i) const {
        my_type a = *this, res = 1;
        while(i){ if(i & 1) res *= a; a *= a; i >>= 1; }
        return res;
    }
    my_type inv() const { return pow(MOD-2); }
    u32 val() const { return x; }
    static u32 get_mod() { return MOD; }
};


void verify_main(){
    using modint = Modint<998244353>;
    using matrix = nachia::MatrixModulo<modint>;

    int N = nachia::cin.nextU32();
    int M = nachia::cin.nextU32();
    int K = nachia::cin.nextU32();

    matrix A(N, M);
    for(int y=0; y<N; y++) for(int x=0; x<M; x++){
        A[y][x] = nachia::cin.nextU32();
    }
    assert(A.height() == N);
    assert(A.width() == M);
    
    matrix B(M, K);
    for(int y=0; y<M; y++) for(int x=0; x<K; x++){
        B[y][x] = nachia::cin.nextU32();
    }
    assert(B.height() == M);
    assert(B.width() == K);

    matrix C = A * B;
    assert(C.height() == N);
    assert(C.width() == K);
    for(int y=0; y<N; y++){
        for(int x=0; x<K; x++){
            if(x != 0) nachia::cout << ' ';
            nachia::cout << C[y][x].val();
        }
        nachia::cout << '\n';
    }
}

}

int main(){
    nachia_verify::verify_main();
    return 0;
}


