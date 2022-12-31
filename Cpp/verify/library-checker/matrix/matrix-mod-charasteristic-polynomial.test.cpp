#define PROBLEM "https://judge.yosupo.jp/problem/characteristic_polynomial"
#include "../../../Include/nachia/linear-modulo/matrix-modulo.hpp"
#include "../../../Include/nachia/linear-modulo/characteristic-polynomial.hpp"
#include "../../../Include/nachia/math-modulo/static-modint.hpp"
#include "../../../Include/nachia/misc/fastio.hpp"

int main(){
    using modint = nachia::StaticModint<998244353>;
    using matrix = nachia::MatrixModulo<modint>;
    int N = nachia::cin.nextU32();
    matrix A(N, N);
    for(int y=0; y<N; y++) for(int x=0; x<N; x++) A[y][x] = modint::raw(nachia::cin.nextU32());
    auto L = nachia::CharacteristicPolynomial(std::move(A));
    for(size_t i=0; i<L.size(); i++) nachia::cout << (i?" ":"") << L[i].val();
    nachia::cout << '\n';
    return 0;
}


