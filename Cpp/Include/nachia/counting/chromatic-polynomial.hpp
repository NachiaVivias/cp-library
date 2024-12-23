#pragma once
#include "../bit-convolution/set-power-series-power-projection.hpp"
#include <vector>
#include <utility>
#include <cassert>

namespace nachia{

template<class Modint>
std::vector<Modint> SetCoverPolynomial(int n, const std::vector<Modint>& table){
    assert(int(table.size()) >= (1 << n));
    int nn = 1 << (n-1);
    auto table2 = std::vector<Modint>(table.begin(), table.begin() + nn);
    table2[0] -= Modint(1);
    std::vector<Modint> weight(nn, 0);
    for(int i=0; i<nn; i++) weight[nn-1-i] = table[nn+i];
    auto powerproj = SpsPowerProjection(n-1, table2, weight, n, true);
    powerproj.insert(powerproj.begin(), Modint(0));
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
