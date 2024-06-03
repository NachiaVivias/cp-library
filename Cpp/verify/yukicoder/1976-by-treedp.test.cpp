#define PROBLEM "https://yukicoder.me/problems/no/1976"
#include "../../Include/nachia/tree/tree-dp.hpp"
#include "../../Include/nachia/misc/fastio.hpp"

int main(){
    using nachia::cin, nachia::cout;
    int N; cin >> N;
    nachia::Graph tree(N, true);
    for(int i=0; i<N-1; i++){
        int u, v; cin >> u >> v; u--; v--;
        tree.addEdge(u, v);
    }

    struct Semiclaster {
        int height = 0;
        int diam = 0;
    };
    auto treedp = nachia::TreeDP<Semiclaster>::Solver(
        tree,
        [](int){ return Semiclaster(); },
        [](Semiclaster a, Semiclaster b, int){
            Semiclaster res;
            res.height = std::max(a.height, b.height);
            res.diam = std::max({ a.diam, b.diam, a.height + b.height });
            return res;
        },
        [](Semiclaster a, int, int){
            Semiclaster res;
            res.height = a.height + 1;
            res.diam = std::max(a.diam, res.height);
            return res;
        }
    );

    int ans = N;
    for(int e=0; e<N-1; e++){
        int diam1 = treedp.getAtEdge(tree[e].from, e).diam;
        int diam2 = treedp.getAtEdge(tree[e].to, e).diam;
        int cr_ans = (diam1 + 1) / 2 + (diam2 + 1) / 2 + 1;
        cr_ans = std::max({ cr_ans, diam1, diam2 });
        ans = std::min(ans, cr_ans);
    }

    cout << ans << '\n';
    return 0;
}
