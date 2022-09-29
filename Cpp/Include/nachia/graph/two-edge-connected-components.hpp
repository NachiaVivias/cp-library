#pragma once
#include "../graph/graph.hpp"
#include "../graph/dfs-tree.hpp"
#include <vector>
#include <utility>
#include <cassert>

namespace nachia{

struct TwoEdgeConnectedComponents{
    Graph mG;
    int m_numComponent;
    std::vector<int> m_color;
    TwoEdgeConnectedComponents(Graph G = Graph(0, true)){
        assert(G.isUndirected());
        int n = G.numVertices(), m = G.numEdges();
        if(n == 0){ mG = G; m_numComponent = 0; return; }
        std::vector<int> P, ord, I(n); {
            auto dfsTree = DfsTree::Construct<false>(G);
            P = std::move(dfsTree.parent);
            ord = std::move(dfsTree.dfsOrd);
            for(int i=0; i<n; i++) I[ord[i]] = i;
        }
        std::vector<int> rev = I, PE(n, -1);
        for(int e=0; e<m; e++){
            int v = G[e].from, w = G[e].to;
            if(I[v] < I[w]) std::swap(v, w);
            if(P[v] == w && PE[v] < 0){ PE[v] = e; }
            else rev[v] = std::min(rev[v], I[w]);
        }
        for(int i=n-1; i>=0; i--){
            int v = ord[i], w = P[v];
            if(w >= 0) rev[w] = std::min(rev[w], rev[v]);
        }
        m_numComponent = 0;
        m_color.resize(n);
        for(int v : ord){
            if(rev[v] == I[v]) m_color[v] = m_numComponent++;
            else m_color[v] = m_color[P[v]];
        }
        mG = std::move(G);
    }
    int numComponents() const noexcept { return m_numComponent; }
    CsrArray<int> getTeccVertices() const {
        int n = mG.numVertices();
        std::vector<std::pair<int, int>> res(n);
        for(int i=0; i<n; i++) res[i] = { m_color[i], i };
        return CsrArray<int>::Construct(numComponents(), res);
    }
    // bridge : -1
    std::vector<int> getEdgeMapping() const {
        std::vector<int> res(mG.numEdges(), -1);
        for(int i=0; i<mG.numEdges(); i++) if(m_color[mG[i].from] == m_color[mG[i].to]) res[i] = m_color[mG[i].from];
        return res;
    }
};

}

