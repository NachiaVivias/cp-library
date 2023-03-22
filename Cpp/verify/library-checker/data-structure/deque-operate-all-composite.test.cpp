#define PROBLEM "https://judge.yosupo.jp/problem/deque_operate_all_composite"
#include "../../../Include/nachia/array/deque-operate-aggregation.hpp"
#include "../../../Include/nachia/misc/fastio.hpp"


namespace Problem{

using u32 = unsigned int;
using u64 = unsigned long long;

const u32 MOD = 998244353;

struct Val{
    u32 a;
    u32 b;

    u32 operator()(u32 x) const { return ((u64)x * a + b) % MOD; }
};

Val operator+(Val l, Val r){
    Val res;
    res.a = (u64)l.a * r.a % MOD;
    res.b = ((u64)l.b * r.a + r.b) % MOD;
    return res;
}
}

int main(){
    using nachia::cin, nachia::cout;
    nachia::DequeOperateAggregation<Problem::Val> ds;

    int Q; cin >> Q;
    for(int i=0; i<Q; i++){
        int ty; cin >> ty;
        if(ty == 0){
            unsigned int a, b; cin >> a >> b;
            ds.pushFront({ a, b });
        }
        if(ty == 1){
            unsigned int a, b; cin >> a >> b;
            ds.pushBack({ a, b });
        }
        if(ty == 2){
            ds.popFront();
        }
        if(ty == 3){
            ds.popBack();
        }
        if(ty == 4){
            unsigned int x; cin >> x;
            unsigned int ans = ds.allProd()(x);
            cout << ans << '\n';
        }
    }
    return 0;
}
