#define PROBLEM "https://judge.yosupo.jp/problem/static_range_lis_query"
#include "../../../Include/nachia/range-query/range-lis.hpp"
#include "../../../Include/nachia/misc/fastio.hpp"

int main(){
    using nachia::cin;
    using nachia::cout;
    int N; cin >> N;
    int Q; cin >> Q;
    std::vector<int> A(N);
    for(int i=0; i<N; i++) cin >> A[i];
    auto ds = nachia::RangeLis(A);
    for(int i=0; i<Q; i++){
        int l, r; cin >> l >> r;
        cout << ds.lis(l, r) << '\n';
    }
    return 0;
}
