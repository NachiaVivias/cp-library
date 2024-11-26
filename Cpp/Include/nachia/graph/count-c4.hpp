#pragma once
#include <algorithm>
#include <vector>
#include "../graph/graph.hpp"

namespace nachia{

// simple graph
// for each edge
// O( n + m sqrt(m) ) time
template<class Weight>
std::vector<Weight> CountC4Simple(
    int n,
    Graph g,
    std::vector<Weight> W
){
    int m = int(W.size());
    
    // less incident edges, smaller index
    std::vector<int> deg(n);
    for(auto [u,v] : g){ deg[u]++; deg[v]++; }
    std::vector<int> I(n); for(int i=0; i<n; i++) I[i] = i;
    std::sort(I.begin(), I.end(), [&](int l, int r){ return deg[l] < deg[r]; });
    {
        std::vector<int> O(n);
        for(int i=0; i<n; i++) O[I[i]] = i;
        for(auto& [u,v] : g){ u = O[u], v = O[v]; }
    }

    for(auto& e : g) if(e.from < e.to) e.reverse();
    
    // adjacency list

    std::vector<int> estart(n);
    for(int i=0; i<n-1; i++) estart[i+1] = estart[i] + deg[I[i]];
    std::vector<int> eend = estart;
    std::vector<int> eid(m*2);
    std::vector<int> eto(m*2);

    for(int e=0; e<m; e++){
        auto [v,w] = g[e];
        eid[eend[v]] = e;
        eto[eend[v]] = w;
        eend[v]++;
    }
    std::vector<int> eendx = eend;
    for(int v=0; v<n; v++){
        for(int i=estart[v]; i<eendx[v]; i++){
            int e = eid[i];
            int w = eto[i];
            eid[eend[w]] = e;
            eto[eend[w]] = v;
            eend[w]++;
        }
    }
    
    std::vector<Weight> c(n); // c[x] : number of paths(v --> w --> x)
    std::vector<Weight> ans(m);
    for(int v=n-1; v>=0; v--){
        for(int i=estart[v]; i<eend[v]; i++){
            int evw = eid[i];
            int w = eto[i];
            eend[w] -= 1; // remove w -> v
            for(int j=estart[w]; j<eend[w]; j++){
                int ewx = eid[j];
                int x = eto[j];
                c[x] += W[evw] * W[ewx];
            }
        }
        for(int i=estart[v]; i<eend[v]; i++){
            int evw = eid[i];
            int w = eto[i];
            for(int j=estart[w]; j<eend[w]; j++){
                int ewx = eid[j];
                int x = eto[j];
                Weight val = c[x] - W[evw] * W[ewx];
                ans[evw] += val * W[ewx];
                ans[ewx] += val * W[evw];
            }
        }
        for(int i=estart[v]; i<eend[v]; i++){
            int w = eto[i];
            for(int j=estart[w]; j<eend[w]; j++) c[eto[j]] = 0;
        }
    }
    return ans;
}

// for each edge
// O( n + m sqrt(m) ) time
template<class Weight>
std::vector<Weight> CountC4(
    int n,
    Graph g,
    std::vector<Weight> W
){
    int m = int(W.size());
    for(auto& e : g) if(e.to < e.from) e.reverse();
    std::vector<int> I(m);
    for(int i=0; i<m; i++) I[i] = i;
    std::sort(I.begin(), I.end(), [&](int l, int r){
        return g[l].from != g[r].from ? g[l].from < g[r].from : g[l].to < g[r].to;
    });

    std::vector<int> Q(m);
    Graph g2;
    int g2sz = 0;
    std::vector<Weight> W2;
    for(auto e : I){
        if(g2sz == 0 || g2[g2sz-1].from != g[e].from || g2[g2sz-1].to != g[e].to){
            g2.addEdge(g[e].from, g[e].to);
            W2.push_back(0);
            g2sz++;
        }
        W2.back() += W[e];
        Q[e] = g2sz-1;
    }

    auto simple_res = CountC4Simple<Weight>(n, std::move(g2), std::move(W2));
    std::vector<Weight> ans(m);
    for(int e=0; e<m; e++) ans[e] = simple_res[Q[e]];
    return ans;
}

} // namespace nachia
