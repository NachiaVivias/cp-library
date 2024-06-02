#pragma once
#include <vector>
#include "../linear-modulo/matrix-modulo.hpp"

namespace nachia {

template<class Modint>
Modint CountDirectedSpanningTrees(
    int N, int v,
    const nachia::MatrixModulo<Modint>& G
){
    using Matrix = nachia::MatrixModulo<Modint>;
    Matrix lap = Matrix(N, N);
    for(int i=0; i<N; i++) for(int j=0; j<N; j++){
        lap[i][j] -= G[i][j]; lap[i][i] += G[i][j];
    }
    Matrix lapd = Matrix(N-1, N-1);
    for(int i=0; i<N; i++) for(int j=0; j<N; j++) if(i!=v && j!=v){
        lapd[i-(i>v?1:0)][j-(j>v?1:0)] = lap[i][j];
    }
    return lapd.det();
}

} // namespace nachia
