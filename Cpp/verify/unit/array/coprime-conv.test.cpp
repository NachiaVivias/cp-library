#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include "../unit-lib.hpp"

#include "../../../Include/nachia/array/divisor-convolution.hpp"
#include <cassert>

int Gcd(int a, int b){
    if(b == 0) return a;
    return Gcd(b, a%b);
}

void solve(nachia::Xoshiro256pp& rng){
    int N = rng.random_unsigned(100, 300);
    std::vector<unsigned long long> A(N);
    for(int i=1; i<N; i++) A[i] = rng.rng64();
    std::vector<unsigned long long> expect(N);
    for(int i=1; i<N; i++) for(int j=1; j<N; j++) if(Gcd(i,j) == 1){
        expect[i] += A[j];
    }
    nachia::SumForCoprimeIndex(A);
    for(int i=1; i<N; i++) assert(A[i] == expect[i]);
}
