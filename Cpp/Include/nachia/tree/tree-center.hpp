#pragma once
#include "../graph/graph.hpp"
#include "tree-diameter.hpp"

namespace nachia{

// size 1 : center is a node
// size 2 : center is an edge between them
std::vector<int> UnitTreeCenter(const CsrArray<int>& T){
    auto diameter = UnitTreeDiameter(T);
    if(diameter.size() % 2 == 1){
        return { diameter[diameter.size() / 2] };
    }
    return { diameter[diameter.size() / 2 - 1], diameter[diameter.size() / 2] };
}

std::vector<int> UnitTreeCenter(const Graph& T){
    return UnitTreeCenter(T.getAdjacencyArray(true));
}

} // namespace nachia

