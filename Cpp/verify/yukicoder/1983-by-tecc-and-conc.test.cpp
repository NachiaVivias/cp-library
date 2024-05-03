#define PROBLEM "https://yukicoder.me/problems/no/1983"
#include "../../Include/nachia/graph/two-edge-connected-components.hpp"
#include "../../Include/nachia/graph/connected-components.hpp"
#include "../../Include/nachia/misc/fastio.hpp"

int main(){
    using nachia::cin;
    using nachia::cout;
    int N, M, Q; cin >> N >> M >> Q;
    nachia::Graph graph(N, true);
    for(int i=0; i<M; i++){
        int u; cin >> u;
        int v; cin >> v;
        graph.addEdge(u-1, v-1);
    }

    auto tecc = nachia::TwoEdgeConnectedComponents(graph).getEdgeMapping();

    nachia::Graph graph2(N, true);
    for(int i=0; i<M; i++) if(tecc[i] == -1) graph2.addEdge(graph[i].from, graph[i].to);

    auto con = nachia::ConnectedComponents(graph2).getMapping();

    for(int i=0; i<Q; i++){
        int u; cin >> u;
        int v; cin >> v;
        bool ans = con[u-1] == con[v-1];
        cout << (ans ? "Yes\n" : "No\n");
    }
    return 0;
}
