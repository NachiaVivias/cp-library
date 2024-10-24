#pragma once
#include "../graph/strongly-connected-components.hpp"
#include "../graph/graph.hpp"
#include "../set/dsu-fast.hpp"
#include "../array/csr-array.hpp"
#include <vector>
#include <algorithm>

namespace nachia {

CsrArray<int> IncrementalSccOffline(Graph graph){
    int n = graph.numVertices();
    int m = graph.numEdges();
    std::vector<int> sep(m+1), newconnectivity, ya;
    using Cc = StronglyConnectedComponents;
    {
        auto cc = Cc(graph).getMapping();
        for(int i=0; i<m; i++){
            if(cc[graph[i].from] != cc[graph[i].to]) continue;
            ya.push_back(i);
        }
    }
    auto dfs = [&](auto& dfs, int n, int x, std::vector<int> ya) -> void {
        int m = int(ya.size());
        if(x == m) return;
        if(x + 1 == m){
            auto dsu = nachia::DsuFast(n);
            for(int e=0; e<m; e++){
                auto [u,v] = graph[ya[e]];
                if(dsu.same(u,v)) continue;
                dsu.merge(u,v);
                sep[ya[x]+1] += 1; newconnectivity.push_back(ya[e]);
            }
            return;
        }
        int nn = 0;
        {
            std::vector<int> mp(n, -1);
            for(int e=0; e<m; e++){
                auto& [u,v] = graph[ya[e]];
                if(mp[u] == -1) mp[u] = nn++;
                if(mp[v] == -1) mp[v] = nn++;
                u = mp[u];
                v = mp[v];
            }
        }
        int y = (x + m) / 2;
        std::vector<int> cc = [&](){
            Graph tg(nn, false, y);
            for(int e=0; e<y; e++) tg[e] = graph[ya[e]];
            return Cc(std::move(tg)).getMapping();
        }();
        std::vector<int> yal, yar;
        for(int e=0; e<x; e++){
            auto [u,v] = graph[ya[e]];
            (cc[u] == cc[v] ? yal : yar).push_back(ya[e]);
        }
        int xl = int(yal.size());
        for(int e=x; e<y; e++){
            auto [u,v] = graph[ya[e]];
            (cc[u] == cc[v] ? yal : yar).push_back(ya[e]);
        }
        int xr = int(yar.size());
        for(int e=y; e<m; e++){
            auto [u,v] = graph[ya[e]];
            if(cc[u] != cc[v]) yar.push_back(ya[e]);
        }
        dfs(dfs, nn, xl, std::move(yal));
        for(int e : yar){
            auto& [u,v] = graph[e];
            u = cc[u]; v = cc[v];
        }
        dfs(dfs, nn, xr, std::move(yar));
    };
    dfs(dfs, n, 0, std::move(ya));
    for(int i=0; i<m; i++) sep[i+1] += sep[i];
    return CsrArray<int>::FromRaw(std::move(newconnectivity), std::move(sep));
}

} // namespace nachia
