#define PROBLEM "https://judge.yosupo.jp/problem/incremental_scc"
#include "../../../Include/nachia/graph/incremental-scc-offline.hpp"
#include "../../../Include/nachia/set/dsu-fast.hpp"
#include "../../../Include/nachia/misc/fastio.hpp"
#include <vector>

void Exit(const char* e){ puts(e); exit(0); }

int main(){
    using nachia::cin;
    using nachia::cout;
    constexpr int MOD = 998244353;
    int N, M; cin >> N >> M;
    std::vector<int> X(N);
    for(int i=0; i<N; i++) cin >> X[i];
    auto g = nachia::Graph::Input(cin, N, false, M, 0);
    int ans = 0;
    auto res = nachia::IncrementalSccOffline(g);
    auto dsu = nachia::DsuFast(N);
    for(int i=0; i<M; i++){
        for(int e : res[i]){
            int u = dsu[g[e].from];
            int v = dsu[g[e].to];
            int w = dsu.merge(u,v);
            ans = ((long long)X[u] * X[v] + ans) % MOD;
            X[w] = X[u] + X[v];
            if(X[w] >= MOD) X[w] -= MOD;
        }
        cout << ans << '\n';
    }
    return 0;
}
