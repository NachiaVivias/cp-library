#define PROBLEM "https://judge.yosupo.jp/problem/counting_c4"
#include "../../../Include/nachia/graph/count-c4.hpp"
#include "../../../Include/nachia/misc/fastio.hpp"

int main(){
    using nachia::cin;
    using nachia::cout;
    int N, M; cin >> N >> M;
    auto g = nachia::Graph::Input(cin, N, true, M, 0);
    auto ans = nachia::CountC4(N, std::move(g), std::vector<long long>(M,1));
    for(int i=0; i<M; i++){
        if(i) cout << ' ';
        cout << ans[i];
    } cout << '\n';
    return 0;
}
