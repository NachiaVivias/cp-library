#define PROBLEM "https://judge.yosupo.jp/problem/queue_operate_all_composite"
#include "../../../Include/nachia/array/deque-operate-aggregation.hpp"
#include "../../../Include/nachia/misc/fastio.hpp"
#include "affine-mod-strict.hpp"

int main(){
    using nachia::cin, nachia::cout;
    using Val = AffineModStrict<998244353>;
    nachia::DequeOperateAggregation<Val> ds(Val::Identity());

    int Q; cin >> Q;
    for(int i=0; i<Q; i++){
        int ty; cin >> ty;
        if(ty == 0){
            unsigned int a, b; cin >> a >> b;
            ds.pushBack({ a, b });
        }
        if(ty == 1){
            ds.popFront();
        }
        if(ty == 2){
            unsigned int x; cin >> x;
            unsigned int ans = ds.allProd().eval(x);
            cout << ans << '\n';
        }
    }
    return 0;
}
