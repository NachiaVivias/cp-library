#pragma once
#include "../graph/graph.hpp"
#include <cassert>
#include <vector>

namespace nachia{

struct ConnectedComponents{
    ConnectedComponents(const CsrArray<int>& adj){
        int n = adj.size();
        std::vector<int> res(n, -1), O(n);
        int Ci = 0, p1 = 0, p0 = 0;
        for(int i=0; i<n; i++) if(res[i] < 0){
            res[i] = Ci++; O[p1++] = i;
            for( ; p0<p1; p0++){
                int v = O[p0];
                for(int w : adj[v]) if(res[w] < 0){
                    res[w] = res[v];
                    O[p1++] = w;
                }
            }
        }
        m_color = std::move(res);
        m_numC = Ci;
    }
    ConnectedComponents(const Graph& G = Graph(0, true)) : ConnectedComponents(G.getAdjacencyArray(true)) {}
    int numComponents() const noexcept { return m_numC; }
    const std::vector<int>& getMapping() const { return m_color; }
private:
    int m_numC;
    std::vector<int> m_color;
};

} // namespace nachia
