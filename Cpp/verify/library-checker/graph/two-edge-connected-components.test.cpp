#define PROBLEM "https://judge.yosupo.jp/problem/two_edge_connected_components"
#include "../../../Include/nachia/graph/two-edge-connected-components.hpp"
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
    auto tecc = nachia::TwoEdgeConnectedComponents(G);
    auto teccv = tecc.getTecVertices();
    int teccCnt = tecc.numComponents();

    printf("%d\n", teccCnt);
    for(int i=0; i<teccCnt; i++){
        printf("%d\n", (int)teccv[i].size());
        for(auto v : teccv[i]) printf(" %d", v);
        printf("\n");
    }
    return 0;
}
