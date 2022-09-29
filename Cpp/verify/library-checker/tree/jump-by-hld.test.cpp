#define PROBLEM "https://judge.yosupo.jp/problem/jump_on_tree"
#include "../../../Include/nachia/tree/heavy-light-decomposition.hpp"
#include "../../../Include/nachia/graph/graph.hpp"

#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int N; std::cin >> N;
    int Q; std::cin >> Q;
    std::vector<std::pair<int,int>> edges(N-1);
    for(int i=0; i<N-1; i++) std::cin >> edges[i].first >> edges[i].second;
    auto hld = nachia::HeavyLightDecomposition(nachia::Graph(N, edges, true).getAdjacencyArray());
    for(int i=0; i<Q; i++){
        int s,t,d; std::cin >> s >> t >> d;
        std::cout << hld.la(s, t, d) << '\n';
    }
    return 0;
}
