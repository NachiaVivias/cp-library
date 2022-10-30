#define PROBLEM "https://judge.yosupo.jp/problem/biconnected_components"
#include "../../../Include/nachia/graph/biconnected-components.hpp"
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

    cout << bccnt << '\n';
    for(int i=0; i<bccnt; i++){
        cout << (int)bcv[i].size();
        for(auto v : bcv[i]) cout << ' ' << v;
        cout << '\n';
    }
    return 0;
}
