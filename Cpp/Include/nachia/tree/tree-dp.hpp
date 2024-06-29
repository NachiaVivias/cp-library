#pragma once
#include "../graph/graph.hpp"
#include <vector>
#include <utility>
#include <algorithm>
#include <type_traits>

namespace nachia{


template<class S>
class TreeDP{
private:

template<
    class NodeInitializer,
    class RakeFunc,
    class CompressFunc,
    typename std::enable_if_t<std::is_invocable_r_v<S, NodeInitializer, int>, void*> = nullptr,
    typename std::enable_if_t<std::is_invocable_r_v<S, RakeFunc, S, S, int>, void*> = nullptr,
    typename std::enable_if_t<std::is_invocable_r_v<S, CompressFunc, S, int, int>, void*> = nullptr
>
class Inner{
private:
    std::vector<S> low;
    std::vector<S> high;
    std::vector<int> XorEdge;
    std::vector<int> P;
    RakeFunc rake;
    CompressFunc compress;

public:

    // S rake(S a, S b)
    // S compress(S a, int edgeIndex, int newRoot)
    Inner(const Graph& tree, NodeInitializer _node, RakeFunc _rake, CompressFunc _compress)
        : rake(std::move(_rake))
        , compress(std::move(_compress))
    {
        int n = tree.numVertices();
        auto adj = tree.getEdgeIndexArray(true);
        std::vector<S> node; node.reserve(n);
        for(int v=0; v<n; v++) node.push_back(_node(v));
        XorEdge.resize(n-1);
        for(int i=0; i<n-1; i++) XorEdge[i] = tree[i].from ^ tree[i].to;
        std::vector<int> bfs(n, 0);
        int bfsi = 1;
        P.assign(n, -1);
        for(int v : bfs){
            for(int e : adj[v]){
                int w = v ^ XorEdge[e];
                if(P[v] != e){ P[w] = e; bfs[bfsi++] = w; }
            }
        }
        low = node;
        for(int i=n-1; i>=1; i--){
            int w = bfs[i];
            int v = w ^ XorEdge[P[w]];
            low[v] = rake(low[v], compress(low[w], P[w], v), v);
        }
        
        high = node;
        for(int i=0; i<n; i++){
            int v = bfs[i];
            int C = adj[v].size();
            S fold = node[0];
            if(v != 0) fold = compress(high[v], P[v], v);
            for(int ci=C-1; ci>=0; ci--){
                int e = adj[v][ci];
                if(P[v] == e) continue;
                int w = v ^ XorEdge[e];
                high[w] = fold;
                fold = rake(compress(low[w], e, v), fold, v);
            }
            fold = node[v];
            for(int ci=0; ci<C; ci++){
                int e = adj[v][ci];
                if(P[v] == e) continue;
                int w = v ^ XorEdge[e];
                high[w] = rake(high[w], fold, v);
                fold = rake(fold, compress(low[w], e, v), v);
            }
        }
    }

    int edgeBetween(int u, int v){
        if(P[u] >= 0 && XorEdge[P[u]] == (u^v)) return P[u];
        return P[v];
    }

    S getAtVtx(int i){
        if(i == 0) return low[i];
        return rake(compress(high[i], P[i], i), low[i], i);
    }
    S getAtEdge(int root, int edge){
        if(P[root] == edge) return low[root];
        return high[root ^ XorEdge[edge]];
    }
};

public:

// S node(int root)
// S rake(S a, S b, int root)
// S compress(S a, int edgeIndex, int newRoot)
template<
    class NodeInitializer,
    class RakeFunc,
    class CompressFunc
>
static auto Solver(
    const Graph& tree,
    NodeInitializer node,
    RakeFunc rake,
    CompressFunc compress)
{
    return Inner<NodeInitializer, RakeFunc, CompressFunc>(
        tree, std::move(node), std::move(rake), std::move(compress));
}

};

} // namespace nachia
