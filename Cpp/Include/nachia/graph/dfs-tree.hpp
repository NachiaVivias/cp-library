#pragma once
#include "../graph/graph.hpp"

namespace nachia{

struct DfsTree{
    std::vector<int> dfsOrd;
    std::vector<int> parent;

    template<bool OutOrd>
    static DfsTree Construct(const CsrArray<int>& adj, int root = 0){
        DfsTree res;
        int n = adj.size();
        res.dfsOrd.resize(n);
        int Oi = 0;
        std::vector<int> eid(n, 0), parent(n, -2);
        for(int s=root; Oi<n; s == n-1 ? s=0 : ++s) if(parent[s] == -2){
            int p = s;
            parent[p] = -1;
            while(0 <= p){
                if(eid[p] == (OutOrd ? (int)adj[p].size() : 0)) res.dfsOrd[Oi++] = p;
                if(eid[p] == (int)adj[p].size()){ p = parent[p]; continue; }
                int nx = adj[p][eid[p]++];
                if(parent[nx] != -2) continue;
                parent[nx] = p;
                p = nx;
            }
            s++; if(s == n) s=0;
        }
        res.parent = std::move(parent);
        return res;
    }
    template<bool OutOrd>
    static DfsTree Construct(const Graph& g, int root = 0){ return Construct<OutOrd>(g.getAdjacencyArray(), root); }
};

} // namespace nachia
