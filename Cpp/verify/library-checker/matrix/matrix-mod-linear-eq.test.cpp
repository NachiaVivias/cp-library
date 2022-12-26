#define PROBLEM "https://judge.yosupo.jp/problem/system_of_linear_equations"
#include "../../../Include/nachia/linear-modulo/matrix-modulo.hpp"
#include "../../../Include/nachia/linear-modulo/linear-equation.hpp"
#include "../../../Include/nachia/math-modulo/static-modint.hpp"
#include "../../../Include/nachia/misc/fastio.hpp"


int main() {
    using modint = nachia::StaticModint<998244353>;
    using matrix = nachia::MatrixModulo<modint>;

    int h,w; nachia::cin >> h >> w;
    matrix A(h, w+1);
    for(int i=0; i<h; i++) for(int j=0; j<w; j++) A[i][j] = modint::raw(nachia::cin.nextU32());
    for(int i=0; i<h; i++) A[i][w] = -modint(modint::raw(nachia::cin.nextU32()));
    auto sol = nachia::LinearEquation(std::move(A));
    if(sol.height() == 0){ nachia::cout << "-1\n"; }
    else{
        nachia::cout << (sol.height()-1) << '\n';
        for(int i=0; i<w; i++) nachia::cout << (i?" ":"") << sol[0][i].val();
        nachia::cout << '\n';
        for(int i=1; i<sol.height(); i++){
            for(int j=0; j<sol.width()-1; j++) nachia::cout << (j?" ":"") << sol[i][j].val();
            nachia::cout << '\n';
        }
    }
    return 0;
}

