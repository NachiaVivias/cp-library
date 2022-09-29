#define PROBLEM "https://judge.yosupo.jp/problem/biconnected_components"
#include "../../../Include/nachia/graph/biconnected-components.hpp"
#include <cstdio>
#include <algorithm>
#include <cassert>

void Exit(const char* e){ puts(e); exit(0); }

int main() {
    int n; scanf("%d", &n);
    int m; scanf("%d", &m);
    std::vector<std::pair<int, int>> edges(m);
    for(auto& [u,v] : edges){
        scanf("%d", &u);
        scanf("%d", &v);
    }

    auto G = nachia::Graph(n, edges, true);
    auto bc = nachia::BiconnectedComponents(G);
    auto bcv = bc.getBcVertices();
    auto bct = bc.getBcTree();
    auto bce = bc.getBcEdges();
    int bccnt = bc.numComponents();

    if(bcv.size() != bccnt) Exit("bcv.size() != bccnt");
    if(bct.numVertices() != n + bccnt) Exit("bct.numVertices() != n + bccnt");
    if(bce.size() != bccnt) Exit("bce.size() != bccnt");
    if(bce.fullSize() != m) Exit("bce.fullSize() != m");

    std::vector<int> vis(n, -1);
    for(int i=0; i<bccnt; i++){
        for(int v : bcv[i]) vis[v] = i;
        for(int e : bce[i]){
            if(vis[G[e].from] != i) Exit("vis[G[e].from] != i");
            if(vis[G[e].to] != i) Exit("vis[G[e].to] != i");
        }
    }

    printf("%d\n", bccnt);
    for(int i=0; i<bccnt; i++){
        printf("%d\n", (int)bcv[i].size());
        for(auto v : bcv[i]) printf(" %d", v);
        printf("\n");
    }
    return 0;
}
