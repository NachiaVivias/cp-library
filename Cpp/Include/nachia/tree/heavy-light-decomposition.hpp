#pragma once
#include "../array/csr-array.hpp"
#include "../graph/graph.hpp"
#include <vector>
#include <algorithm>

namespace nachia{

struct HeavyLightDecomposition{
private:

    int N;
    std::vector<int> P;
    std::vector<int> PP;
    std::vector<int> PD;
    std::vector<int> D;
    std::vector<int> I;

    std::vector<int> rangeL;
    std::vector<int> rangeR;

public:

    HeavyLightDecomposition(const CsrArray<int>& E = CsrArray<int>::Construct(1, {}), int root = 0){
        N = E.size();
        P.assign(N, -1);
        I = {root};
        I.reserve(N);
        for(int i=0; i<(int)I.size(); i++){
            int p = I[i];
            for(int e : E[p]) if(P[p] != e){
                I.push_back(e);
                P[e] = p;
            }
        }
        std::vector<int> Z(N, 1);
        std::vector<int> nx(N, -1);
        PP.resize(N);
        for(int i=0; i<N; i++) PP[i] = i;
        for(int i=N-1; i>=1; i--){
            int p = I[i];
            Z[P[p]] += Z[p];
            if(nx[P[p]] == -1) nx[P[p]] = p;
            if(Z[nx[P[p]]] < Z[p]) nx[P[p]] = p;
        }

        for(int p : I) if(nx[p] != -1) PP[nx[p]] = p;

        PD.assign(N,N);
        PD[root] = 0;
        D.assign(N,0);
        for(int p : I) if(p != root){
            PP[p] = PP[PP[p]];
            PD[p] = std::min(PD[PP[p]], PD[P[p]]+1);
            D[p] = D[P[p]]+1;
        }
        
        rangeL.assign(N,0);
        rangeR.assign(N,0);
        
        for(int p : I){
            rangeR[p] = rangeL[p] + Z[p];
            int ir = rangeR[p];
            for(int e : E[p]) if(P[p] != e) if(e != nx[p]){
                rangeL[e] = (ir -= Z[e]);
            }
            if(nx[p] != -1){
                rangeL[nx[p]] = rangeL[p] + 1;
            }
        }

        I.resize(N);
        for(int i=0; i<N; i++) I[rangeL[i]] = i;
    }
    
    HeavyLightDecomposition(const Graph& tree, int root = 0)
        : HeavyLightDecomposition(tree.getAdjacencyArray(true), root) {}

    int numVertices() const { return N; }
    int depth(int p) const { return D[p]; }
    int toSeq(int vtx) const { return rangeL[vtx]; }
    int toVtx(int seqidx) const { return I[seqidx]; }
    int toSeq2In(int vtx) const { return rangeL[vtx] * 2 - D[vtx]; }
    int toSeq2Out(int vtx) const { return rangeR[vtx] * 2 - D[vtx] - 1; }
    int parentOf(int v) const { return P[v]; }
    int heavyRootOf(int v) const { return PP[v]; }
    int heavyChildOf(int v) const {
        if(toSeq(v) == N-1) return -1;
        int cand = toVtx(toSeq(v) + 1);
        if(PP[v] == PP[cand]) return cand;
        return -1;
    }

    int lca(int u, int v) const {
        if(PD[u] < PD[v]) std::swap(u, v);
        while(PD[u] > PD[v]) u = P[PP[u]];
        while(PP[u] != PP[v]){ u = P[PP[u]]; v = P[PP[v]]; }
        return (D[u] > D[v]) ? v : u;
    }

    int dist(int u, int v) const {
        return depth(u) + depth(v) - depth(lca(u,v)) * 2;
    }

    struct Range{
        int l; int r;
        int size() const { return r-l; }
        bool includes(int x) const { return l <= x && x < r; }
    };

    std::vector<Range> path(int r, int c, bool include_root = true, bool reverse_path = false) const {
        if(PD[c] < PD[r]) return {};
        std::vector<Range> res(PD[c]-PD[r]+1);
        for(int i=0; i<(int)res.size()-1; i++){
            res[i] = { rangeL[PP[c]], rangeL[c]+1 };
            c = P[PP[c]];
        }
        if(PP[r] != PP[c] || D[r] > D[c]) return {};
        res.back() = { rangeL[r]+(include_root?0:1), rangeL[c]+1 };
        if(res.back().l == res.back().r) res.pop_back();
        if(!reverse_path) std::reverse(res.begin(),res.end());
        else for(auto& a : res) a = { N - a.r, N - a.l };
        return res;
    }

    Range subtree(int p) const { return { rangeL[p], rangeR[p] }; }

    int median(int x, int y, int z) const {
        return lca(x,y) ^ lca(y,z) ^ lca(x,z);
    }

    int la(int from, int to, int d) const {
        if(d < 0) return -1;
        int g = lca(from,to);
        int dist0 = D[from] - D[g] * 2 + D[to];
        if(dist0 < d) return -1;
        int p = from;
        if(D[from] - D[g] < d){ p = to; d = dist0 - d; }
        while(D[p] - D[PP[p]] < d){
            d -= D[p] - D[PP[p]] + 1;
            p = P[PP[p]];
        }
        return I[rangeL[p] - d];
    }

    struct ChildrenIterRange {
    struct Iter {
        const HeavyLightDecomposition& hld; int s;
        int operator*() const { return hld.toVtx(s); }
        Iter& operator++(){
            s += hld.subtree(hld.I[s]).size();
            return *this;
        }
        Iter operator++(int) const { auto a = *this; return ++a; }
        bool operator==(Iter& r) const { return s == r.s; }
        bool operator!=(Iter& r) const { return s != r.s; }
    };
        const HeavyLightDecomposition& hld; int v;
        Iter begin() const { return { hld, hld.rangeL[v] + 1 }; }
        Iter end() const { return { hld, hld.rangeR[v] }; }
    };
    ChildrenIterRange children(int v) const {
        return ChildrenIterRange{ *this, v };
    }
};

} // namespace nachia
