#pragma once
#include "../graph/graph.hpp"
#include "../array/csr-array.hpp"
#include <vector>

namespace nachia{

// list of nodes through the diameter path
std::vector<int> UnitTreeDiameter(const CsrArray<int>& T){
    int n = T.size();
    std::vector<int> I(n, 0);
    std::vector<int> P(n, -1);
    auto ii = I.begin();
    for(int i=0; i<(int)I.size(); i++){
        int p = I[i];
        for(int e : T[p]) if(P[p] != e){
            P[e] = p;
            *++ii = e;
        }
    }
    P[I[n-1]] = -1;
    for(int i=n-1; i>=0; i--){
        int p = I[i];
        for(int e : T[p]) if(P[p] != e){
            P[e] = p;
            *--ii = e;
        }
    }
    std::vector<int> res = { I[0] };
    int sz = 0, szp = res[0];
    while(P[szp] != -1){ sz++; szp = P[szp]; }
    res.reserve(sz);
    while(P[res.back()] != -1){ res.push_back(P[res.back()]);}
    return res;
}

std::vector<int> UnitTreeDiameter(const Graph& T){
    return UnitTreeDiameter(T.getAdjacencyArray(true));
}

} // namespace nachia
