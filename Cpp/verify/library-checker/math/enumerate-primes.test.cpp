#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_primes"
#include "../../../Include/nachia/math/prime-sieve-explicit.hpp"
#include <iostream>

struct ios_do_not_sync{
    ios_do_not_sync(){
        ::std::ios::sync_with_stdio(false);
        ::std::cin.tie(nullptr);
    }
} ios_do_not_sync_instance;

int main(){
    using namespace std;
    int N,A,B; cin >> N >> A >> B;
    int pi_N = nachia::PrimeCountingExplicit(N);
    vector<int> X;
    for(int p=B; p<pi_N; p+=A) X.push_back(nachia::NthPrimeExplicit(p));

    cout << pi_N << ' ' << X.size() << '\n';
    for(int i=0; i<(int)X.size(); i++){
        if(i) cout << ' ';
        cout << X[i];
    }
    cout << '\n';
    return 0;
}
