#pragma once
#include "../graph/graph.hpp"
#include "../array/csr-array.hpp"
#include "../graph/dfs-tree.hpp"
#include <vector>

namespace nachia{

class BiconnectedComponents{
private:
    int mn, mm, mnum_bcs;
    Graph mG;
    std::vector<std::pair<int,int>> m_bcVtxPair;
public:
    BiconnectedComponents(Graph G = Graph(0, true)){
        int n = mn = G.numVertices();
        int m = mm = G.numEdges();
        mG = std::move(G);
        if(n == 0){ mnum_bcs = 0; return; }
        auto adj = mG.getAdjacencyArray();

        auto dfstree = DfsTree::Construct<false>(adj);
        std::vector<int> vtxToDfsi(n), parent, low;
        for(int i=0; i<n; i++) vtxToDfsi[dfstree.dfsOrd[i]] = i;
        parent = std::move(dfstree.parent);
        low = vtxToDfsi;
        
        for(int p=0; p<n; p++) for(int e : adj[p]) low[p] = std::min(low[p], vtxToDfsi[e]);

        for(int i=n-1; i>=0; i--){
            int p = dfstree.dfsOrd[i];
            int pp = parent[p];
            if(pp >= 0) low[pp] = std::min(low[pp], low[p]);
        }
        
        int num_bcs = 0;
        std::vector<int> res(m);
        for(int p : dfstree.dfsOrd) if(parent[p] >= 0){
            int pp = parent[p];
            if(low[p] < vtxToDfsi[pp]){
                low[p] = low[pp];
                m_bcVtxPair.push_back({ low[p], p });
            }
            else{
                low[p] = num_bcs++;
                m_bcVtxPair.push_back({ low[p], pp });
                m_bcVtxPair.push_back({ low[p], p });
            }
        }
        for(int s=0; s<mn; s++) if(adj[s].size() == 0) m_bcVtxPair.push_back(std::make_pair(num_bcs++, s));
        mnum_bcs = num_bcs;
    }

    int numComponents() const { return mnum_bcs; }

    CsrArray<int> getBcVertices() const {
        return CsrArray<int>::Construct(numComponents(), m_bcVtxPair);
    }

    Graph getBcTree() const {
        int bct_n = mn + mnum_bcs;
        std::vector<std::pair<int, int>> res = m_bcVtxPair;
        for(auto& e : res) e.first += mn;
        return Graph(bct_n, std::move(res), true);
    }

    CsrArray<int> getBcEdges() const {
        auto bct = getBcTree().getAdjacencyArray();
        int z = bct.size();
        std::vector<int> bfsP(z, -1), bfsD(z, 0), bfs(z);
        int p0 = 0, p1 = 0;
        for(int s=0; s<z; s++) if(bfsP[s] < 0){
            for(bfs[p1++]=s; p0<p1; p0++){
                int p = bfs[p0];
                for(auto e : bct[p]) if(bfsP[p] != e){
                    bfsP[e] = p;
                    bfsD[e] = bfsD[p] + 1;
                    bfs[p1++] = e;
                }
            }
        }
        std::vector<std::pair<int,int>> res(mm);
        for(int i=0; i<mm; i++){
            int u = mG[i].from, v = mG[i].to;
            res[i].first = bfsP[(bfsD[u] <= bfsD[v]) ? v : u] - mn;
            res[i].second = i;
        }
        return CsrArray<int>::Construct(mnum_bcs, res);
    }
};

} // namespace nachia
