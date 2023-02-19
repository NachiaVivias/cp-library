#define PROBLEM "https://judge.yosupo.jp/problem/point_add_rectangle_sum"
#include "../../../Include/nachia/set/dsu.hpp"
#include "../../../Include/nachia/misc/fastio.hpp"

int main(){
    using nachia::cin;
    using nachia::cout;
    int N; cin >> N;
    int Q; cin >> Q;
    nachia::Dsu dsu(N);
    for(int i=0; i<Q; i++){
        int t, u, v; cin >> t >> u >> v;
        if(t == 0) dsu.merge(u, v);
        if(t == 1) cout << (dsu.same(u, v) ? 1 : 0) << '\n';
    }
    return 0;
}
