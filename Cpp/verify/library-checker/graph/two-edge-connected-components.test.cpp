#define PROBLEM "https://judge.yosupo.jp/problem/two_edge_connected_components"
#include "../../../Include/nachia/graph/two-edge-connected-components.hpp"
#include "../../../Include/nachia/misc/fastio.hpp"
#include <algorithm>
#include <cassert>

void Exit(const char* e){ puts(e); exit(0); }

int main() {
    using nachia::cin;
    using nachia::cout;

    int n = cin.nextU32();
    int m = cin.nextU32();
    std::vector<std::pair<int, int>> edges(m);
    for(auto& [u,v] : edges){
        u = cin.nextU32();
        v = cin.nextU32();
    }

    auto G = nachia::Graph(n, edges, true);
    auto tecc = nachia::TwoEdgeConnectedComponents(G);
    auto teccv = tecc.getTeccVertices();
    int teccCnt = tecc.numComponents();

    cout << teccCnt << '\n';
    for(int i=0; i<teccCnt; i++){
        cout << (int)teccv[i].size();
        for(auto v : teccv[i]) cout << ' ' << v;
        cout << '\n';
    }
    return 0;
}
