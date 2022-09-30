#define PROBLEM "https://judge.yosupo.jp/problem/scc"
#include "../../../Include/nachia/graph/strongly-connected-components.hpp"
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

    auto G = nachia::Graph(n, edges, false);
    auto scc = nachia::SCC(G);
    auto sccv = scc.getCsr();
    int scccnt = scc.numComponents();

    printf("%d\n", scccnt);
    for(int i=0; i<scccnt; i++){
        printf("%d", (int)sccv[i].size());
        for(auto v : sccv[i]) printf(" %d", v);
        printf("\n");
    }
    return 0;
}
