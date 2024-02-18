#pragma once
#include <algorithm>
#include <vector>
#include "../graph/graph.hpp"

namespace nachia{

// for each edge
template<class Int>
std::vector<Int> CountC4(nachia::Graph graph){
    int n = graph.numVertices();
    int m = graph.numEdges();
    std::vector<int> O(n);
    for(auto e : graph){ O[e.from]++; O[e.to]++; }
    std::vector<int> I(n); for(int i=0; i<n; i++) I[i] = i;
    std::sort(I.begin(), I.end(), [&](int l, int r){ return O[l] < O[r]; });
    for(int i=0; i<n; i++) O[I[i]] = i;
    for(auto& e : graph) if(O[e.from] < O[e.to]) e.reverse();
    auto adj = graph.getEdgeIndexArray(false);
    struct Edge{ int li; int to; };
    std::vector<Edge> nx(m*2, {-1,-1});
    std::vector<int> head(n, -1);
    for(int v : I){
        for(int e : adj[v]){
            int w = graph[e].xorval() ^ v;
            nx[e*2] = { head[v], w };
            head[v] = e*2;
        }
    }
    for(int v : I){
        for(int e : adj[v]){
            int w = graph[e].xorval() ^ v;
            nx[e*2+1] = { head[w], v };
            head[w] = e*2+1;
        }
    }
    std::reverse(I.begin(), I.end());
    std::vector<int> c(n);
    std::vector<Int> ans(m);
    for(int v : I){
        for(int evw=head[v]; evw>=0; evw=nx[evw].li){
            int w = nx[evw].to;
            head[w] = nx[head[w]].li; // nx[head[w]].to == v
            for(int ewx=head[w]; ewx>=0; ewx=nx[ewx].li){
                c[nx[ewx].to]++;
            }
        }
        for(int evw=head[v]; evw>=0; evw=nx[evw].li){
            int w = nx[evw].to;
            for(int ewx=head[w]; ewx>=0; ewx=nx[ewx].li){
                int x = nx[ewx].to;
                Int val = Int(c[x] - 1);
                ans[evw/2] += val;
                ans[ewx/2] += val;
            }
        }
        for(int evw=head[v]; evw>=0; evw=nx[evw].li){
            int w = nx[evw].to;
            for(int ewx=head[w]; ewx>=0; ewx=nx[ewx].li) c[nx[ewx].to] = 0;
        }
    }
    return ans;
}

} // namespace nachia
