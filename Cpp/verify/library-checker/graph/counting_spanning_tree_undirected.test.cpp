#define PROBLEM "https://judge.yosupo.jp/problem/counting_spanning_tree_undirected"
#include "../../../Include/nachia/modulo/static-modint.hpp"
#include "../../../Include/nachia/counting/directed-spanning-trees.hpp"
#include "../../../Include/nachia/misc/fastio.hpp"

int main(){
    using nachia::cin;
    using nachia::cout;
    using Modint = nachia::StaticModint<998244353>;
    using Mat = nachia::MatrixModulo<Modint>;
    int N, M; cin >> N >> M;
    auto mat = Mat(N, N);
    for(int i=0; i<M; i++){
        int u,v; cin >> u >> v;
        mat[v][u] += 1;
        mat[u][v] += 1;
    }
    auto ans = nachia::CountDirectedSpanningTrees(N, 0, mat);
    cout << ans.val() << '\n';
    return 0;
}
