#pragma once
#include "../graph/graph.hpp"

namespace nachia{

struct DfsTree{
    std::vector<int> dfsOrd;
    std::vector<int> parent;

    template<bool OutOrd>
    static DfsTree Construct(const CsrArray<int>& adj){
        DfsTree res;
        int n = adj.size();
        res.dfsOrd.resize(n);
        int Oi = 0;
        std::vector<int> eid(n, 0), parent(n, -2);
        for(int s=0; s<n; s++) if(parent[s] == -2){
            int p = s;
            if(p >= n) p -= n;
            parent[p] = -1;
            while(0 <= p){
                if(eid[p] == (OutOrd ? (int)adj[p].size() : 0)) res.dfsOrd[Oi++] = p;
                if(eid[p] == (int)adj[p].size()){ p = parent[p]; continue; }
                int nx = adj[p][eid[p]++];
                if(parent[nx] != -2) continue;
                parent[nx] = p;
                p = nx;
            }
        }
        res.parent = std::move(parent);
        return res;
    }
    template<bool OutOrd>
    static DfsTree Construct(const Graph& g){ return Construct<OutOrd>(g.getAdjacencyArray()); }
};

} // namespace nachia
