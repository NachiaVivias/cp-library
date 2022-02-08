#define PROBLEM "https://judge.yosupo.jp/problem/system_of_linear_equations"
#include "../../../Include/nachia/linear/matrix-modulo.hpp"


#include <iostream>


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

    int h,w; std::cin >> h >> w;
    matrix A(h, w+1);
    for(int i=0; i<h; i++) for(int j=0; j<w; j++){ int a; std::cin >> a; A[i][j] = a; }
    for(int i=0; i<h; i++){ int a; std::cin >> a; A[i][w] = -modint(a); }
    auto sol = A.linear_equation();
    if(sol.height() == 0){ std::cout << "-1\n"; }
    else{
        std::cout << (sol.height()-1) << "\n";
        for(int i=0; i<w; i++){ if(i) std::cout << " "; std::cout << sol[0][i].val(); } std::cout << "\n";
        for(int i=1; i<sol.height(); i++){
            for(int j=0; j<sol.width()-1; j++){ if(j) std::cout << " "; std::cout << sol[i][j].val(); }
            std::cout << "\n";
        }
    }
}

}


struct ios_do_not_sync{
    ios_do_not_sync(){
        std::ios::sync_with_stdio(false);
        std::cin.tie(nullptr);
    }
} ios_do_not_sync_instance;

int main() {
    nachia_verify::verify_main();
    return 0;
}

