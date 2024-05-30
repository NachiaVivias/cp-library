#define PROBLEM "https://judge.yosupo.jp/problem/chromatic_polynomial"
#include "../../../Include/nachia/graph/counting/chromatic-polynomial.hpp"
#include <vector>
#include <utility>
#include <cstdio>

namespace nachia{

template<unsigned int MOD>
struct StaticModint{
private:
    using u64 = unsigned long long;
    unsigned int x;
public:

    using my_type = StaticModint;
    template< class Elem >
    static Elem safe_mod(Elem x){
        if(x < 0){
            if(0 <= x+MOD) return x + MOD;
            return MOD - ((-(x+MOD)-1) % MOD + 1);
        }
        return x % MOD;
    }

    StaticModint() : x(0){}
    StaticModint(const my_type& a) : x(a.x){}
    StaticModint& operator=(const my_type&) = default;
    template< class Elem >
    StaticModint(Elem v) : x(safe_mod(v)){}
    my_type& operator+=(const my_type& r) noexcept { auto t = x + r.x; if(t >= MOD) t -= MOD; x = t; return *this; }
    my_type operator+(const my_type& r) const noexcept { my_type res = *this; return res += r; }
    my_type& operator-=(const my_type& r) noexcept { auto t = x + MOD - r.x; if(t >= MOD) t -= MOD; x = t; return *this; }
    my_type operator-(const my_type& r) const noexcept { my_type res = *this; return res -= r; }
    my_type operator-() const noexcept { my_type res = *this; res.x = ((res.x == 0) ? 0 : (MOD - res.x)); return res; }
    my_type& operator*=(const my_type& r)noexcept { x = (u64)x * r.x % MOD; return *this; }
    my_type operator*(const my_type& r) const noexcept { my_type res = *this; return res *= r; }
    unsigned int val() const noexcept { return x; }
};

} // namespace nachia


int main(){
    using Modint = nachia::StaticModint<998244353>;
    int N, M; scanf("%d%d", &N, &M);
    std::vector<std::vector<int>> adj(N, std::vector<int>(N));
    for(int i=0; i<M; i++){
        int u,v; scanf("%d%d", &u, &v);
        adj[u][v] = 1;
    }
    auto ans = nachia::ChromaticPolynomial<Modint>(adj);
    for(int i=0; i<=N; i++){
        if(i) printf(" ");
        printf("%u", ans[i].val());
    } printf("\n");
    return 0;
}
