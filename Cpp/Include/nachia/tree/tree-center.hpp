#pragma once

#include "tree-diameter.hpp"


namespace nachia{

// size 1 : center is a node
// size 2 : center is an edge between them
std::vector<int> UnitTreeCenter(const AdjacencyList& T){
    auto diameter = UnitTreeDiameter(T);
    if(diameter.size() % 2 == 1){
        return { diameter[diameter.size() / 2] };
    }
    return { diameter[diameter.size() / 2 - 1], diameter[diameter.size() / 2] };
}

} // namespace nachia

