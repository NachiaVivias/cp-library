#define PROBLEM "https://judge.yosupo.jp/problem/chromatic_number"

#include "../../../Include/nachia/graph/chromatic-number.hpp"
#include "../../../Include/nachia/misc/fastio.hpp"
#include <cassert>



int main(){
    using nachia::cin;
    using nachia::cout;

    int N = cin.nextU32();
    int M = cin.nextU32();
    std::vector<std::vector<int>> E(N, std::vector<int>(N, 0));
    for(int i=0; i<M; i++){
        int u = cin.nextU32();
        int v = cin.nextU32();
        E[u][v] = E[v][u] = 1;
    }
    int ans = nachia::ChromaticNumber(E);
    static constexpr unsigned int MODLIST[] = { 1048583, 1000000009, 1073741827, 2147483629, 2147483647 };
    int qans[5] = {
        nachia::ChromaticNumberByMod<MODLIST[0]>(E),
        nachia::ChromaticNumberByMod<MODLIST[1]>(E),
        nachia::ChromaticNumberByMod<MODLIST[2]>(E),
        nachia::ChromaticNumberByMod<MODLIST[3]>(E),
        nachia::ChromaticNumberByMod<MODLIST[4]>(E)
    };
    for(int i=0; i<5; i++) assert(qans[i] >= ans);
    cout << ans << "\n";
    return 0;
}
