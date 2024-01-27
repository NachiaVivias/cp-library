#define PROBLEM "https://judge.yosupo.jp/problem/eulerian_trail_directed"

#include "../../../Include/nachia/graph/eulerian-trail.hpp"
#include "../../../Include/nachia/misc/fastio.hpp"


int main(){
    using nachia::cin;
    using nachia::cout;
    int T; cin >> T;
    for(int t=0; t<T; t++){
        int N, M; cin >> N >> M;
        auto graph = nachia::Graph::Input(cin, N, false, M, 0);
        auto path = nachia::EulerianTrail(graph);
        if(path.length < 0){
            cout << "No\n";
        } else {
            cout << "Yes\n";
            int v = path.start;
            cout << v;
            for(int i=0; i<int(path.edges.size()); i++){
                v ^= graph[path.edges[i]].xorval();
                cout << ' ' << v;
            } cout << '\n';
            for(int i=0; i<int(path.edges.size()); i++){
                if(i) cout << ' ';
                cout << path.edges[i];
            } cout << '\n';
        }
    }
    return 0;
}
