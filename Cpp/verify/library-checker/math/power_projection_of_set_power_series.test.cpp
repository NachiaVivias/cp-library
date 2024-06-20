#define PROBLEM "https://judge.yosupo.jp/problem/power_projection_of_set_power_series"
#include "../../../Include/nachia/bit-convolution/set-power-series-power-projection.hpp"
#include "../../../Include/nachia/misc/fastio.hpp"
#include <vector>
#include <utility>

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
    using nachia::cin;
    using nachia::cout;
    int N, M; cin >> N >> M;
    std::vector<Modint> A(1<<N);
    for(int i=0; i<(1<<N); i++){ int a; cin >> a; A[i] = Modint(a); }
    std::vector<Modint> W(1<<N);
    for(int i=0; i<(1<<N); i++){ int a; cin >> a; W[i] = Modint(a); }
    auto ans = nachia::SpsPowerProjection(N, A, W, M);
    for(int i=0; i<M; i++){
        if(i) cout << ' ';
        cout << ans[i].val();
    } cout << '\n';
    return 0;
}
