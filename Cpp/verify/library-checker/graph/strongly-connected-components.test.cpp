#define PROBLEM "https://judge.yosupo.jp/problem/scc"
#include "../../../Include/nachia/graph/strongly-connected-components.hpp"
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

    auto G = nachia::Graph(n, edges, false);
    auto scc = nachia::StronglyConnectedComponents(G);
    auto sccv = scc.getCsr();
    int scccnt = scc.numComponents();

    cout << scccnt << '\n';
    for(int i=0; i<scccnt; i++){
        cout << (int)sccv[i].size();
        for(auto v : sccv[i]) cout << ' ' << v;
        cout << '\n';
    }
    return 0;
}
