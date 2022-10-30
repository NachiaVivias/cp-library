#define PROBLEM "https://judge.yosupo.jp/problem/jump_on_tree"
#include "../../../Include/nachia/tree/heavy-light-decomposition.hpp"
#include "../../../Include/nachia/graph/graph.hpp"
#include "../../../Include/nachia/misc/fastio.hpp"

int main() {
    using nachia::cin;
    using nachia::cout;
    int N; cin >> N;
    int Q; cin >> Q;
    std::vector<std::pair<int,int>> edges(N-1);
    for(int i=0; i<N-1; i++) cin >> edges[i].first >> edges[i].second;
    auto hld = nachia::HeavyLightDecomposition(nachia::Graph(N, edges, true).getAdjacencyArray());
    for(int i=0; i<Q; i++){
        int s,t,d; cin >> s >> t >> d;
        cout << hld.la(s, t, d) << '\n';
    }
    return 0;
}
