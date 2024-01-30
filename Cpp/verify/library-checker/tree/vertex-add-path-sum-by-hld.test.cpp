#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_path_sum"
#include "../../../Include/nachia/tree/heavy-light-decomposition.hpp"
#include "../../../Include/nachia/graph/graph.hpp"
#include "../../../Include/nachia/misc/fastio.hpp"
#include <cstdint>

struct BIT{
    std::vector<int64_t> A;
    BIT(int n){
        A.assign(n+1,0);
    }
    void add(int p, int64_t x){
        p++;
        while(p < (int)A.size()){
            A[p] += x;
            p += p & -p;
        }
    }
    int64_t sum(int r){
        int p = r;
        int64_t res = 0;
        while(p > 0){
            res += A[p];
            p -= p & -p;
        }
        return res;
    }
    int64_t sum(int l, int r){
        return sum(r) - sum(l);
    }
};

int main() {
    using nachia::cin;
    using nachia::cout;
    
    int N,Q; cin >> N >> Q;
    std::vector<int> A(N);
    for(int i=0; i<N; i++) cin >> A[i];
    std::vector<std::pair<int, int>> edges(N-1);
    for(auto& e : edges) cin >> e.first >> e.second;

    auto hld = nachia::HeavyLightDecomposition(nachia::Graph(N, edges, true).getAdjacencyArray());
    BIT rq(N);

    for(int i=0; i<N; i++) rq.add(hld.toSeq(i),A[i]);

    for(int i=0; i<Q; i++){
        int t; cin >> t;
        if(t == 0){
            int p,x; cin >> p >> x;
            rq.add(hld.toSeq(p),x);
        }
        if(t == 1){
            int u,v; cin >> u >> v;
            int g = hld.lca(u,v);
            int64_t res = 0;
            for(auto I : hld.path(g,u,true)) res += rq.sum(I.l, I.r);
            for(auto I : hld.path(g,v,false)) res += rq.sum(I.l, I.r);
            cout << res << "\n";
        }
    }
    return 0;
}
