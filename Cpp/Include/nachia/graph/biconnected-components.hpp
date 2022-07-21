#pragma once

#include "../graph/adjacency-list.hpp"
#include "../graph/adjacency-list-indexed.hpp"

#include <vector>

namespace nachia{

class BiconnectedComponents{
private:
    int mn;
    int mm;
    int mnum_bcs;
    std::vector<std::pair<int, int>> medges;
    std::vector<int> edgeidx_to_bcidx;
public:
    BiconnectedComponents(int n, std::vector<std::pair<int, int>> edges){

        mn = n;
        int m = edges.size();
        medges = std::move(edges);
        nachia::AdjacencyListEdgeIndexed adj(n, medges, true);

        std::vector<int> dfsi_to_vtx(n);
        std::vector<int> vtx_to_dfsi(n);
        std::vector<int> linked_over(n, -1);
        std::vector<int> dfs_parent(n, -1);
        int dfsi = 0;

        auto dfs1 = [&](int p, auto self)->int {
            vtx_to_dfsi[p] = dfsi;
            dfsi_to_vtx[dfsi] = p;
            int backedge = dfsi;
            dfsi++;
            for(auto [nx,i] : adj[p]){
                if(dfs_parent[nx] != -1){
					backedge = std::min(backedge, vtx_to_dfsi[nx]);
				}
                else{
                    dfs_parent[nx] = i;
                    int link = self(nx, self);
                    backedge = std::min(backedge, link);
                    linked_over[nx] = (link < vtx_to_dfsi[p]) ? 1 : 0;
                }
            }
            return backedge;
        };
        for(int i=0; i<n; i++) if(dfs_parent[i] == -1){
            dfs_parent[i] = -2;
            dfs1(i, dfs1);
        }
        
        std::vector<int> res(m);
        auto dfs2 = [&](int p, int bcid, int& maxbcid, auto self)-> void {
            if(dfs_parent[p] < 0){
                for(auto [nx,i] : adj[p]) if(dfs_parent[nx] == i){
                    bcid = maxbcid++;
                    self(nx, bcid, maxbcid, self);
                }
                return;
            }
            for(auto [nx,i] : adj[p]) if(dfs_parent[nx] != i) res[i] = bcid;
            for(auto [nx,i] : adj[p]) if(dfs_parent[nx] == i){
                int nx_bcid = bcid;
                if(!linked_over[nx]) nx_bcid = maxbcid++;
                self(nx, nx_bcid, maxbcid, self);
            }
        };
        int bcid = 0;
        for(int i=0; i<n; i++) if(dfs_parent[i] < 0) dfs2(i, -1, bcid, dfs2);
        edgeidx_to_bcidx = std::move(res);
        mm = m;
        mnum_bcs = bcid;
    }

    int get_num_bcs() const { return mnum_bcs; }

    std::vector<std::vector<int>> get_bcs() const {
        std::vector<std::vector<int>> res(mnum_bcs);
        for(int i=0; i<mm; i++){
            res[edgeidx_to_bcidx[i]].push_back(i);
        }
        return res;
    }

    AdjacencyList get_bct() const {
        int bct_n = mn + mnum_bcs;
        AdjacencyList bc_edgelists; {
            std::vector<int> buf(mnum_bcs+1);
            for(int bci : edgeidx_to_bcidx) ++buf[bci];
            for(int i=1; i<=mnum_bcs; i++) buf[i] += buf[i-1];
            std::vector<int> E(buf.back());
            for(int i=0; i<mm; i++) E[--buf[edgeidx_to_bcidx[i]]] = i;
            bc_edgelists = AdjacencyList::from_raw(std::move(E), std::move(buf));
        }
        std::vector<std::pair<int, int>> res(bct_n * 2 - 1);
        int resi = 0;
        int bci = 0;
        std::vector<int> visited(mn, -1);
        for(bci=0 ; bci<mnum_bcs; bci++){
            for(int e : bc_edgelists[bci]){
                auto [u,v] = medges[e];
                if(visited[u] != bci){ visited[u] = bci; res[resi++] = {mn+bci,u}; }
                if(visited[v] != bci){ visited[v] = bci; res[resi++] = {mn+bci,v}; }
            }
        }
        for(int i=0; i<mn; i++) if(visited[i] == -1) res[resi++] = {bct_n++,i};
        res.resize(resi);
        return AdjacencyList(bct_n, res, true);
    }
};

} // namespace nachia
