
#define PROBLEM "https://judge.yosupo.jp/problem/counting_primes"

#include "../../../Include/nachia/math/counting-primes.hpp"
#include <iostream>

struct ios_do_not_sync{
    ios_do_not_sync(){
        ::std::ios::sync_with_stdio(false);
        ::std::cin.tie(nullptr);
    }
} ios_do_not_sync_instance;

int main(){
    using namespace std;
    long long n; std::cin >> n;
    long long ans = nachia::CountingPrimes(n);
    cout << ans << '\n';
    return 0;
}
