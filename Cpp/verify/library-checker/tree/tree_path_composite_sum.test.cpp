#define PROBLEM "https://judge.yosupo.jp/problem/tree_path_composite_sum"
#include "../../../Include/nachia/tree/tree-dp.hpp"
#include "../../../Include/nachia/graph/graph.hpp"
#include "../../../Include/nachia/math-modulo/static-modint.hpp"
#include "../../../Include/nachia/misc/fastio.hpp"
#include <array>


int main(){
    using nachia::cin;
    using nachia::cout;
    using Modint = nachia::StaticModint<998244353>;

    int N; cin >> N;

    auto tree = nachia::Graph(N, true);

    std::vector<Modint> A(N), B(N-1), C(N-1);

    for(int i=0; i<N; i++){
        int x; cin >> x; A[i] = Modint::raw(x);
    }

    for(int i=0; i<N-1; i++){
        int u, v, b, c; cin >> u >> v >> b >> c;
        tree.addEdge(u, v);
        B[i] = Modint::raw(b);
        C[i] = Modint::raw(c);
    }
    

    using SemiCluster = std::array<Modint, 2>;

    auto treeDp = nachia::TreeDP<SemiCluster>::Solver(
        tree,
        [](int) -> SemiCluster { return {0,0}; },
        [&](SemiCluster a, SemiCluster b, int) -> SemiCluster {
            return { a[0]+b[0], a[1]+b[1] };
        },
        [&](SemiCluster a, int e, int r) -> SemiCluster {
            int c = tree[e].from ^ tree[e].to ^ r;
            return { C[e] * (a[1] + 1) + B[e] * (a[0] + A[c]), a[1] + 1 };
        }
    );

    for(int i=0; i<N; i++){
        if(i) cout << ' ';
        Modint ans = treeDp.getAtVtx(i)[0] + A[i];
        cout << ans.val();
    }
    cout << '\n';
    return 0;
}
