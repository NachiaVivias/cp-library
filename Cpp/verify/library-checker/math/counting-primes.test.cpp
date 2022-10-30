#define PROBLEM "https://judge.yosupo.jp/problem/counting_primes"
#include "../../../Include/nachia/math/counting-primes.hpp"
#include "../../../Include/nachia/misc/fastio.hpp"

int main(){
    nachia::cout << nachia::CountingPrimes(nachia::cin.nextI64()) << '\n';
    return 0;
}
