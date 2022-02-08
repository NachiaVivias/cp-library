#define PROBLEM "https://judge.yosupo.jp/problem/chromatic_number"

#include "../../../Include/nachia/graph/chromatic-number.hpp"

#include <iostream>
#include <cassert>



int main(){
    using namespace std;
    int N,M; cin >> N >> M;
    vector<vector<int>> E(N,vector<int>(N,0));
    for(int i=0; i<M; i++){
        int u,v; cin >> u >> v;
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

struct ios_do_not_sync{
  ios_do_not_sync(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
  }
} ios_do_not_sync_instance;


