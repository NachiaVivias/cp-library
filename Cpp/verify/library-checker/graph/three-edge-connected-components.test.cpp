#define PROBLEM "https://judge.yosupo.jp/problem/three_edge_connected_components"
#include "../../../Include/nachia/graph/three-edge-connected-components.hpp"
#include "../../../Include/nachia/misc/fastio.hpp"
#include <algorithm>
#include <cassert>

void Exit(const char* e){ puts(e); exit(0); }

int main() {
    using nachia::cin;
    using nachia::cout;

    int n = cin.nextU32();
    int m = cin.nextU32();
    auto G = nachia::Graph::Input(cin, n, true, m, 0);
    
    auto thecc = nachia::ThreeEdgeConnectedComponents(G);
    auto csr = thecc.get3EdgeCCVertices();
    cout << thecc.num3EdgeCCComponents() << '\n';
    for(int i=0; i<csr.size(); i++){
        cout << csr[i].size();
        for(int v : csr[i]) cout << ' ' << v;
        cout << '\n';
    }
    return 0;
}
