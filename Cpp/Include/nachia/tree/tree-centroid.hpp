#pragma once

#include "../graph/adjacency-list.hpp"


namespace nachia{

// size 1 : center is a node
// size 2 : center is an edge between them
std::vector<int> UnitTreeCentroid(const AdjacencyList& T){
    int n = T.num_vertices();
    std::vector<int> bfs = {0};
    bfs.reserve(n);
    std::vector<int> Z(n, 1);
    std::vector<int> P(n, -1);
    for(int i=0; i<n; i++){
        int p = bfs[i];
        for(int e : T[p]) if(P[p] != e){
            P[e] = p;
            bfs.push_back(e);
        }
    }
    for(int i=n-1; i>=1; i--) Z[P[bfs[i]]] += Z[bfs[i]];
    int c = 0;
    while(true){
        int nx = -1;
        for(int e : T[c]) if(Z[e]*2 > Z[c]) nx = e;
        if(nx == -1) break;
        Z[c] -= Z[nx]; Z[nx] += Z[c]; c = nx;
    }
    for(int e : T[c]) if(Z[e]*2 == Z[c]) return std::vector{ c, e };
    return { c };
}

} // namespace nachia

