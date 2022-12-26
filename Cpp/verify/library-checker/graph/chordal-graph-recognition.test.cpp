#define PROBLEM "https://judge.yosupo.jp/problem/chordal_graph_recognition"
#include "../../../Include/nachia/misc/fastio.hpp"
#include "../../../Include/nachia/graph/chordal-graph-recognizer.hpp"

int main(){
    using nachia::cin;
    using nachia::cout;
    int N = cin.nextU32();
    int M = cin.nextU32();
    nachia::Graph graph(N, true);
    for(int i=0; i<M; i++){
        int u = cin.nextU32();
        int v = cin.nextU32();
        graph.addEdge(u, v);
    }
    auto chordal = nachia::ChordalGraphRecognizer(std::move(graph));
    
    if(chordal.isChordalGraph()){
        auto peo = chordal.getPerfectEliminationOrdering();
        cout << "YES\n";
        for(int i=0; i<N; i++) cout << (i?" ":"") << peo[i];
        cout << '\n';
    }
    else{
        auto cycle = chordal.findInducedCycle();
        cout << "NO\n";
        cout << cycle.size() << '\n';
        for(int i=0; i<(int)cycle.size(); i++) cout << (i?" ":"") << cycle[i];
        cout << '\n';
    }
    return 0;
}
