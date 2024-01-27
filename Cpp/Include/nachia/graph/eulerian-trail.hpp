#pragma once
#include "../graph/graph.hpp"
#include <algorithm>
#include <vector>

namespace nachia{

auto EulerianTrail(const Graph& graph){
    struct Result {
        int length;
        int start;
        std::vector<int> edges;
    } res;
    res.length = -1;
    auto adj = graph.getEdgeIndexArray();
    int n = graph.numVertices();
    int m = graph.numEdges();
    if(m == 0){
        res.length = 0;
        res.start = 0;
        return res;
    }
    int s = -1;
    if(graph.isUndirected()){
        int codd = 0;
        for(int v=0; v<n; v++) if(adj[v].size() % 2 == 1) codd++;
        if(codd > 2) return res;
        if(codd == 2) for(int v=0; v<n; v++) if(adj[v].size() % 2 == 1) s = v;
    } else {
        std::vector<int> di(n);
        for(auto [v,w] : graph) di[w]++;
        int codd = 0;
        for(int v=0; v<n; v++) codd += std::abs(adj[v].size() - di[v]);
        if(codd > 2) return res;
        if(codd == 2) for(int v=0; v<n; v++) if(adj[v].size() > di[v]) s = v;
    }
    if(s < 0) for(int v=0; v<n; v++) if(adj[v].size() > 0) s = v;
    std::vector<int> ep(n);
    std::vector<int> edges(m);
    std::vector<bool> alive(m, true);
    int pp = 0;
    int pq = m;
    int v = s;
    while(pp < pq){
        if(ep[v] >= adj[v].size()){
            if(pp == 0) return res;
            edges[--pq] = edges[--pp];
            v ^= graph[edges[pq]].xorval();
        } else {
            int e = adj[v][ep[v]++];
            if(!alive[e]) continue;
            alive[e] = false;
            edges[pp++] = e;
            v ^= graph[e].xorval();
        }
    }
    res.length = m;
    res.start = s;
    res.edges = std::move(edges);
    return res;
}

} // namespace nachia
