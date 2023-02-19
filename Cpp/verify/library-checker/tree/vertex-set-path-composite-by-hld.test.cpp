#define PROBLEM "https://judge.yosupo.jp/problem/vertex_set_path_composite"
#include "../../../Include/nachia/tree/heavy-light-decomposition.hpp"
#include "../../../Include/nachia/graph/graph.hpp"
#include "../../../Include/nachia/misc/fastio.hpp"
#include <cstdint>



template<
  class S,
  S op(S, S),
  S e()
>
struct Segtree {

    int N;
    std::vector<S> A;

    void mergev(int i){
        if(i<N) A[i] = op(A[i*2], A[i*2+1]);
    }
    
    Segtree(int n){
        N=1; while (N<n) N*=2;
        A.assign(N*2,e());
    }
    Segtree(const std::vector<S>& a) : Segtree(a.size()){
        for(int i=0; i<a.size(); i++) A[i+N] = a[i];
        for(int i=N-1; i>=1; i--) mergev(i);
    }

    void set(int p, S x){
        p+=N; A[p] = x;
        for(int d=1; (1<<d)<=N; d++) mergev(p>>d);
    }

    S prod(int l, int r, int a=0, int b=0, int i=-1){
        if(i==-1){ a=0; b=N; i=1; }
        if(r<=a || b<=l) return e();
        if(l<=a && b<=r) return A[i];
        S q1 = prod(l, r, a, (a+b)/2, i*2);
        S q2 = prod(l, r, (a+b)/2, b, i*2+1);
        return op(q1, q2);
    }
};



const uint64_t MOD = 998244353;

uint64_t powMOD(uint64_t a, uint64_t i){
    uint64_t r = 1;
    while(i != 0){
        if(i & 1) r = r * a % MOD;
        i /= 2;
        a = a * a % MOD;
    }
    return r;
}

struct RQS {
    uint64_t a,b;
    uint64_t operator()(uint64_t x) const {
        return (a * x + b) % MOD;
    }
    RQS operator()(RQS x) const {
        x.a = x.a * a % MOD;
        x.b = (x.b * a + b) % MOD;
        return x;
    }
    RQS operator~() const {
        uint64_t ia = powMOD(a, MOD-2);
        return RQS{ ia, (MOD - b) * ia % MOD };
    }
};
RQS RQop(RQS l, RQS r){ return r(l); }
RQS RQe(){ return { 1,0 }; }
using RQ = Segtree<RQS,RQop,RQe>;



int main(){
    using nachia::cin;
    using nachia::cout;

    int N, Q; cin >> N >> Q;
    std::vector<RQS> A(N);
    for(auto& a : A) cin >> a.a >> a.b;
    std::vector<std::pair<int, int>> edges(N-1);
    for(auto& e : edges) cin >> e.first >> e.second;

    auto hld = nachia::HeavyLightDecomposition(nachia::Graph(N, edges, true).getAdjacencyArray());
    RQ rq1(N);
    for(int i=0; i<N; i++) rq1.set(hld.toSeq(i),A[i]);
    RQ rq2(N);
    for(int i=0; i<N; i++) rq2.set(N-1-hld.toSeq(i),A[i]);

    for(int i=0; i<Q; i++){
        int t; cin >> t;
        if(t == 0){
            int p,c,d; cin >> p >> c >> d;
            rq1.set(hld.toSeq(p), RQS{(uint64_t)c,(uint64_t)d});
            rq2.set(N-1-hld.toSeq(p), RQS{(uint64_t)c,(uint64_t)d});
        }
        if(t == 1){
            int u,v,x; cin >> u >> v >> x;
            int g = hld.lca(u,v);
            uint64_t px = x;
            for(auto I : hld.path(g,u,false,true)) px = rq2.prod(I.first,I.second)(px);
            for(auto I : hld.path(g,v,true,false)) px = rq1.prod(I.first,I.second)(px);
            cout << px << "\n";
        }
    }
    return 0;
}
