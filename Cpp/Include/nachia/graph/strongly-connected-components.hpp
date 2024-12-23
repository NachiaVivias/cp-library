#pragma once
#include "../graph/graph.hpp"
#include <algorithm>

namespace nachia{

struct StronglyConnectedComponents{
private:
    int m_n;
    CsrArray<int> induce;
    int componentNum;
public:

    StronglyConnectedComponents() : m_n(0), induce(), componentNum(0) {}
    StronglyConnectedComponents(Graph E) {
        int n = E.numVertices();
        m_n = n;
        std::vector<int> O(n);
        {
            auto adj = E.getAdjacencyArray();
            int Oi = n;
            std::vector<int> P(n, -1), EI(n, 0);
            for(int s=0; s<n; s++) if(P[s] == -1){
                P[s] = -2;
                int p = s;
                while(p >= 0){
                    if(EI[p] == adj[p].size()){ O[--Oi] = p; p = P[p]; continue; }
                    int q = adj[p][EI[p]++];
                    if(P[q] == -1){ P[q] = p; p = q; }
                }
            }
        }
        E.reverseEdges();
        auto adj = E.getAdjacencyArray();
        std::vector<int> sep = {0}, csr(n), vis(n,0);
        int p1 = 0, p2 = 0;
        for(int s : O) if(!vis[s]){
            csr[p2++] = s; vis[s] = 1;
            for(; p1<p2; p1++){
                int v = csr[p1];
                for(auto e : adj[v]) if(!vis[e]){ vis[e] = 1; csr[p2++] = e; }
            }
            sep.push_back(p2);
        }
        induce = CsrArray<int>::FromRaw(std::move(csr), std::move(sep));
        componentNum = induce.size();
    }

    int numComponents() const noexcept { return componentNum; }
    const CsrArray<int>& getCsr() const noexcept { return induce; }
    std::vector<int> getMapping() const {
        std::vector<int> res(m_n);
        for(int i=0; i<numComponents(); i++) for(int v : induce[i]) res[v] = i;
        return res;
    }
};

} // namespace nachia
