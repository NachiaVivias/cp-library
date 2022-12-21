#pragma once
#include "../array/csr-array.hpp"
#include "../graph/graph.hpp"

namespace nachia{

struct CentroidDecomposition {
private:
    int n;
    CsrArray<int> adj;
    std::vector<int> cdep;
    std::vector<int> cp;
    std::vector<int> cbfs;
    int maxdep;
public:
    CentroidDecomposition(CsrArray<int> edges) : adj(std::move(edges)){
        n = adj.size();
        std::vector<int> Z(n, 1);
        std::vector<int> P(n, -1);
        std::vector<int> I(n, 0);
        cbfs.resize(n); int cbfsp = 0;
        int quep = 1;
        for(int p : I) for(int e : adj[p]) if(P[p] != e) P[I[quep++] = e] = p;
        for(int i=n-1; i>=1; i--) Z[P[I[i]]] += Z[I[i]];
        cp.assign(n, -1);
        cdep.assign(n, 0);
        quep = 1;
        for(int s : I){
            int par = P[s]; P[s] = -1;
            while(true){
                int nx = -1;
                for(int e : adj[s]) if (Z[e] * 2 > Z[s]) nx = e;
                if(nx == -1) break;
                Z[s] -= Z[nx]; Z[nx] += Z[s];
                P[s] = nx; P[nx] = -1;
                s = nx;
            }
            cbfs[cbfsp++] = s;
            Z[s] = 0;
            if(par != -1){
                cdep[s] = cdep[par] + 1;
                cp[s] = par;
            }
            for(int e : adj[s]) if(Z[e] != 0) I[quep++] = e;
        }
        maxdep = 0;
        for(int a : cdep) maxdep = std::max(maxdep, a);
    }
    CentroidDecomposition(const Graph& g) : CentroidDecomposition(g.getAdjacencyArray(true)) {}
    CentroidDecomposition() : CentroidDecomposition(Graph(1, true)) {}

    int parentOf(int v) const noexcept { return cp[v]; }
    int depthOf(int v) const noexcept { return cdep[v]; }

    struct BFSUnit {
        std::vector<int> I;
        std::vector<int> P;
    };
    BFSUnit bfsLayer(int s, int layer) const {
        BFSUnit res;
        if(cdep[s] < layer) return res;
        res.I.push_back(s);
        res.P.push_back(-1);
        for(int i=0; i<(int)res.I.size(); i++){
            int p = res.I[i];
            for(int e : adj[p]) if(res.P[i] != e){
                if(cdep[e] < layer) continue;
                res.I.push_back(e);
                res.P.push_back(p);
            }
        }
        return res;
    }
};

} // namespace nachia
