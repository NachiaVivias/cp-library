#define PROBLEM "https://judge.yosupo.jp/problem/cartesian_tree"
#include "../../../Include/nachia/array/cartesian-tree.hpp"
#include "../../../Include/nachia/misc/fastio.hpp"

int main(){
    using nachia::cin;
    using nachia::cout;
    int N; cin >> N;
    std::vector<int> A(N);
    for(int i=0; i<N; i++) cin >> A[i];
    auto g = nachia::CartesianTree(A);
    std::vector<int> ans(N);
    for(int i=0; i<N; i++) ans[i] = i;
    for(auto e : g) ans[e.to] = e.from;
    for(int i=0; i<N; i++){
        if(i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}
