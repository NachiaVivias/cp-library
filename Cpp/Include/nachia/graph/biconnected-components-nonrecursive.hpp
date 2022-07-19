#pragma once

#include "../graph/adjacency-list.hpp"
#include "../graph/adjacency-list-indexed.hpp"

#include <vector>

namespace nachia{

class BiconnectedComponentsNonrecursive{
private:
    int mn;
    int mm;
    int mnum_bcs;
    std::vector<std::pair<int, int>> medges;
    std::vector<int> edgeidx_to_bcidx;
public:
    BiconnectedComponentsNonrecursive(int n, ::std::vector<::std::pair<int, int>> edges){

        mn = n;
        int m = edges.size();
        medges = std::move(edges);
        AdjacencyListEdgeIndexed adj(n, medges, true);

        std::vector<int> vtx_to_dfsi(n);
        std::vector<int> dfs_parent(n, -1);
        std::vector<int> dfs_parentp(n, -1);
        std::vector<int> dfs_backedge(n, -1);
        int dfsi = 0;
        
        int num_bcs = 0;
        std::vector<int> res(m);

        std::vector<int> mem(n*2);
        int memi = 0;

        for(int i=0; i<n; i++) if(dfs_parent[i] == -1){
            dfs_parent[i] = -2;
            mem[memi++] = i; mem[memi++] = 0;
            while(memi){
                int ei = mem[--memi];
                int p = mem[--memi];
                if(ei == 0){
                    vtx_to_dfsi[p] = dfs_backedge[p] = dfsi++;
                }
                while(true){
                    if(ei == adj[p].size()){
                        if(0 <= dfs_parentp[p]){
                            dfs_backedge[dfs_parentp[p]] = ::std::min(dfs_backedge[dfs_parentp[p]], dfs_backedge[p]);
                        }
                        break;
                    }
                    auto [nx,i] = adj[p][ei++];
                    if(dfs_parent[nx] != -1){
                        dfs_backedge[p] = ::std::min(dfs_backedge[p], vtx_to_dfsi[nx]);
                    }
                    else{
                        dfs_parent[nx] = i;
                        dfs_parentp[nx] = p;
                        memi++; mem[memi++] = ei;
                        mem[memi++] = nx; mem[memi++] = 0;
                        break;
                    }
                }
            }
        }

        for(int i=0; i<n; i++) if(dfs_parent[i] < 0){
            mem[memi++] = i;
            while(memi){
                int p = mem[--memi];
                if(dfs_parent[p] < 0){
                    for(auto [nx,i] : adj[p]) if(dfs_parent[nx] == i){
                        mem[memi++] = nx; dfs_backedge[nx] = num_bcs++;
                    }
                    continue;
                }
                for(auto [nx,i] : adj[p]){
                    if(dfs_parent[nx] != i) res[i] = dfs_backedge[p];
                    else{
                        mem[memi++] = nx;
                        dfs_backedge[nx] = (dfs_backedge[nx] < vtx_to_dfsi[p]) ? dfs_backedge[p] : num_bcs++;
                    }
                }
            }
        }

        edgeidx_to_bcidx = ::std::move(res);
        mm = m;
        mnum_bcs = num_bcs;
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
        std::vector<int> visited(mn, 1);
        for(bci=0 ; bci<mnum_bcs; bci++){
            for(int e : bc_edgelists[bci]){
                auto [u,v] = medges[e];
                if(visited[u] != 0){ visited[u] = 0; res[resi++] = {mn+bci,u}; }
                if(visited[v] != 0){ visited[v] = 0; res[resi++] = {mn+bci,v}; }
            }
            for(int e : bc_edgelists[bci]){
                auto [u,v] = medges[e];
                visited[u] = visited[v] = 2;
            }
        }
        for(int i=0; i<mn; i++) if(visited[i] == 1) res[resi++] = {bct_n++,i};
        res.resize(resi);
        return AdjacencyList(bct_n, res, true);
    }
};

} // namespace nachia
