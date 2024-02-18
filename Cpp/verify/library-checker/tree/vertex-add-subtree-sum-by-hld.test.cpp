#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_subtree_sum"
#include "../../../Include/nachia/tree/heavy-light-decomposition.hpp"
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
    S get(int p){ return A[N+p]; }

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

struct RQS {
    uint64_t a;
};
RQS RQop(RQS l, RQS r){ return { l.a + r.a }; }
RQS RQe(){ return { 0 }; }
using RQ = Segtree<RQS,RQop,RQe>;



int main(){
    using nachia::cin;
    using nachia::cout;

    int N, Q; cin >> N >> Q;
    std::vector<RQS> A(N);
    for(auto& a : A) cin >> a.a;
    std::vector<std::pair<int,int>> edges(N-1);
    for(int i=1; i<N; i++){
        int p; cin >> p;
        edges[i-1] = { p, i };
    }

    auto hld = nachia::HeavyLightDecomposition(nachia::CsrArray<int>::Construct(N, edges));
    RQ rq(N);
    for(int i=0; i<N; i++) rq.set(hld.toSeq(i), A[i]);

    for(int i=0; i<Q; i++){
        int t; cin >> t;
        if(t == 0){
            int p,x; cin >> p >> x;
            rq.set(hld.toSeq(p), { rq.get(hld.toSeq(p)).a + (uint64_t)x });
        }
        if(t == 1){
            int p; cin >> p;
            auto range = hld.subtree(p);
            uint64_t ans = rq.prod(range.l, range.r).a;
            cout << ans << "\n";
        }
    }
    return 0;
}
