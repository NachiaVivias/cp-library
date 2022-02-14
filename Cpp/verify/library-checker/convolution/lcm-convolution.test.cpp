#define PROBLEM "https://judge.yosupo.jp/problem/lcm_convolution"

#include <iostream>
#include <cassert>
#include <vector>
#include <utility>

#include "../../../Include/nachia/array/divisor-convolution.hpp"

namespace nachia{

template<unsigned int MOD>
struct StaticModint{
private:
    using u64 = unsigned long long;
    unsigned int x;
public:

    using my_type = StaticModint;

    StaticModint() : x(0){}
    StaticModint(unsigned int v) : x(v){}
    unsigned int operator*() const { return x; }
    my_type& operator+=(const my_type& r){ auto t = x + r.x; if(t >= MOD) t -= MOD; x = t; return *this; }
    my_type operator+(const my_type& r) const { my_type res = *this; return res += r; }
    my_type& operator-=(const my_type& r){ auto t = x + MOD - r.x; if(t >= MOD) t -= MOD; x = t; return *this; }
    my_type operator-(const my_type& r) const { my_type res = *this; return res -= r; }
    my_type operator-() const { my_type res = *this; res.x = ((res.x == 0) ? 0 : (MOD - res.x)); return res; }
    my_type& operator*=(const my_type& r){ x = (u64)x * r.x % MOD; return *this; }
    my_type operator*(const my_type& r) const { my_type res = *this; return res *= r; }
    my_type pow(unsigned long long i) const {
        my_type a = *this, res = 1;
        while(i){ if(i & 1) res *= a; a *= a; i >>= 1; }
        return res;
    }
    my_type inv() const { return pow(MOD-2); }
    unsigned int val() const { return x; }
    static unsigned int get_mod() { return MOD; }
    my_type& operator/=(const my_type& r){ return operator*=(r.inv()); }
    my_type operator/(const my_type& r) const { return operator*(r.inv()); }
};

}




int main(){
    using namespace std;
    using modint = nachia::StaticModint<998244353>;

    int N; cin >> N;
    vector<modint> A(N+1);
    for(int i=1; i<=N; i++){ int a; cin >> a; A[i] = a; }
    vector<modint> B(N+1);
    for(int i=1; i<=N; i++){ int a; cin >> a; B[i] = a; }
    
    A = nachia::LcmConvolution(move(A), move(B));
    
    for(int i=1; i<=N; i++){
        if(i != 1) cout << ' ';
        cout << *A[i];
    }
    cout << '\n';
    return 0;
}

struct ios_do_not_sync{
    ios_do_not_sync(){
        std::ios::sync_with_stdio(false);
        std::cin.tie(nullptr);
    }
} ios_do_not_sync_instance;


