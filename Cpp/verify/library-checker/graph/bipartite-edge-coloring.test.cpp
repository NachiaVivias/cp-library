#define PROBLEM "https://judge.yosupo.jp/problem/bipartite_edge_coloring"
#include "../../../Include/nachia/graph/bipartite-edge-coloring.hpp"
#include "../../../Include/nachia/misc/fastio.hpp"
#include <vector>
#include <utility>
#include <algorithm>

int main(){
    using nachia::cin;
    using nachia::cout;
    int L, R, M; cin >> L >> R >> M;
    std::vector<std::pair<int,int>> edges(M);
    for(auto &[u,v] : edges) cin >> u >> v;
    auto ans = nachia::BipartiteEdgeColor(L, R, std::move(edges));
    int k = 1 + *std::max_element(ans.begin(), ans.end());
    cout << k << '\n';
    for(auto a : ans) cout << a << '\n';
    return 0;
}
