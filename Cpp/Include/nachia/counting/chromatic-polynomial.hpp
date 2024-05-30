#pragma once
#include "../bit-convolution/set-power-series-power-projection.hpp"
#include <vector>
#include <utility>
#include <cassert>

namespace nachia{

template<class Modint>
std::vector<Modint> SetCoverPolynomial(int n, std::vector<Modint> table){
    int nn = 1 << n;
    assert(int(table.size()) >= nn);
    table[0] -= Modint(1);
    std::vector<Modint> weight(nn, 0);
    weight[nn-1] = Modint(1);
    auto powerproj = SpsPowerProjection(n, table, weight, n+1, true);
    std::vector<Modint> prod(n+2);
    std::vector<Modint> res(n+1);
    prod[0] = 1;
    for(int i=0; i<=n; i++){
        Modint I = Modint(i);
        for(int j=0; j<=i; j++){ res[j] += prod[j] * powerproj[i]; }
        for(int j=i; j>=0; j--){ prod[j+1] += prod[j]; prod[j] *= -I; }
    }
    return res;
}

template<class Modint>
std::vector<Modint> ChromaticPolynomial(std::vector<std::vector<int>> adjacency_matrix){
    int n = adjacency_matrix.size();
    int nn = 1 << n;
    std::vector<Modint> en(nn,1);
    for(int u=0; u<n; u++) for(int v=0; v<n; v++){
        if(adjacency_matrix[u][v]) en[(1<<u)|(1<<v)] = 0;
    }
    for(int d=0; d<n; d++) for(int i=0; i<nn; i++) if(i&(1<<d)) en[i] *= en[i-(1<<d)];
    return SetCoverPolynomial(n, std::move(en));
}

} // namespace nachia
