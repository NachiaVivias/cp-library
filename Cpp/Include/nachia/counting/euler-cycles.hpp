#pragma once
#include "../counting/directed-spanning-trees.hpp"
#include "../math/combination.hpp"

namespace nachia {

template<class Modint>
Modint CountEulerCycles(
    int N,
    std::vector<std::vector<long long>> G,
    nachia::Comb<Modint>& comb
){
    std::vector<int> nodes;
    Modint mult = 1;
    for(int i=0; i<N; i++){
        long long q = 0;
        for(int j=0; j<N; j++) q += G[i][j] - G[j][i];
        if(q != 0) return 0;
        long long od = 0;
        for(int j=0; j<N; j++) od += G[i][j];
        if(od){
            nodes.push_back(i);
            comb.extend(od);
            mult *= comb.factorial(od - 1);
        }
    }
    int n = nodes.size();
    if(n == 0) return 1;
    auto newG = MatrixModulo<Modint>(n, n);
    for(int i=0; i<n; i++) for(int j=0; j<n; j++){
        newG[i][j] = G[nodes[i]][nodes[j]];
    }
    auto ans = CountDirectedSpanningTrees(n, 0, newG);
    return ans * mult;
}

template<class Modint>
Modint CountEulerCycles(
    int N,
    std::vector<std::vector<long long>> G
){
    nachia::Comb<Modint> comb;
    return CountEulerCycles(N, std::move(G), comb);
}

}
