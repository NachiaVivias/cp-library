#define PROBLEM "https://judge.yosupo.jp/problem/shortest_path"

#include "../../../Include/nachia/graph/dijkstra.hpp"
#include "../../../Include/nachia/graph/graph.hpp"
#include "../../../Include/nachia/misc/fastio.hpp"


int main(){
    struct Weight{
        long long a;
        Weight operator+(Weight r) const { return {a+r.a}; }
        bool operator<(Weight r) const { return a<r.a; }
    };
    struct Weight2{ int a; operator Weight() const { return {a}; } };
    using nachia::cin, nachia::cout;
    int N, M; cin >> N >> M;
    int s, t; cin >> s >> t;
    nachia::Graph G(N, false);
    std::vector<Weight2> W(M);
    for(int i=0; i<M; i++){
        int u,v,c; cin >> u >> v >> c;
        G.addEdge(u, v);
        W[i] = {c};
    }
    long long INF = 1ll << 60;
    auto res = nachia::DijkstraShortestPath(G, W, {{s,{0}}}, Weight{INF});
    if(res.distTo(t).a == INF){
        cout << "-1\n";
    } else {
        auto path = res.pathTo(t);
        cout << res.distTo(t).a << ' ' << path.size() << '\n';
        for(int e : path) cout << G[e].from << ' ' << G[e].to << '\n';
    }
    return 0;
}
