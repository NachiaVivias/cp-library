#define PROBLEM "https://judge.yosupo.jp/problem/counting_eulerian_circuits"
#include "../../../Include/nachia/counting/euler-cycles.hpp"
#include "../../../Include/nachia/modulo/static-modint.hpp"
#include "../../../Include/nachia/misc/fastio.hpp"

int main(){
    using nachia::cin;
    using nachia::cout;
    using Modint = nachia::StaticModint<998244353>;
    int N, M; cin >> N >> M;
    auto graph = std::vector<std::vector<long long>>(N, std::vector<long long>(N));
    for(int i=0; i<M; i++){
        int u,v; cin >> u >> v;
        graph[u][v] += 1;
    }
    auto ans = nachia::CountEulerCycles<Modint>(N, graph);
    cout << ans.val() << '\n';
    return 0;
}
