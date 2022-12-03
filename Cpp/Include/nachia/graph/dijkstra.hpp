#pragma once
#include "../graph/graph.hpp"
#include <vector>
#include <queue>

namespace nachia{

template<class Weight = long long, class Weight2 = Weight>
struct DijkstraShortestPath {
private:
    nachia::Graph g;
    std::vector<Weight> dist;
    std::vector<int> pre;
public:

    DijkstraShortestPath(
        nachia::Graph graph,
        const std::vector<Weight2>& weight,
        const std::vector<std::pair<int, Weight>>& starting,
        const Weight Inf
    ){
        using T = std::pair<Weight, int>;
        g = std::move(graph);
        auto adj = g.getEdgeIndexArray();
        std::vector<Weight> D(g.numVertices(), Inf);
        std::vector<int> E(g.numVertices(), -1);
        struct Comp { bool operator()(T a, T b) const noexcept { return b < a; }; };
        std::priority_queue<T, std::vector<T>, Comp> Q;
        for(auto a : starting) if(a.second < D[a.first]){
            D[a.first] = a.second;
            Q.push({ a.second, a.first });
        }
        while(Q.size()){
            int p = Q.top().second;
            Weight d = Q.top().first; Q.pop();
            if(D[p] < d) continue;
            for(auto e : adj[p]){
                int q = g[e].to;
                Weight nxd = d + Weight(weight[e]);
                if(!(nxd < D[q])) continue;
                E[q] = e;
                D[q] = nxd;
                Q.push({ nxd, q });
            }
        }
        dist = std::move(D);
        pre = std::move(E);
    }

    Weight distTo(int v) const noexcept { return dist[v]; }
    int prevEdge(int v) const noexcept { return pre[v]; }
    std::vector<int> pathTo(int v) const {
        std::vector<int> res;
        while(pre[v] >= 0){
            res.push_back(pre[v]);
            v ^= g[pre[v]].from ^ g[pre[v]].to;
        }
        std::reverse(res.begin(), res.end());
        return res;
    }
};

} // namespace nachia
