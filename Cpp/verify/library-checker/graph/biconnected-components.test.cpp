#define PROBLEM "https://judge.yosupo.jp/problem/biconnected_components"

#include "../../../Include/nachia/graph/biconnected-components.hpp"


#include <iostream>
#include <algorithm>

int main() {

    int n; std::cin >> n;
    int m; std::cin >> m;
    std::vector<std::pair<int, int>> edges(m);
    for(auto& [u,v] : edges){
        u; std::cin >> u;
        v; std::cin >> v;
    }

    auto bct = nachia::BiconnectedComponents(n, edges).get_bct();

    int bccnt = bct.num_vertices() - n;
    for(int i=0; i<n; i++) if(bct[i].size() == 0) bccnt++;

    std::cout << bccnt << '\n';

    std::vector<std::vector<int>> ansbuf(bccnt);
    int ansbufItr = 0;
    
    for(int bcidx=n; bcidx < bct.num_vertices(); bcidx++) ansbuf[ansbufItr++] = std::vector<int>(bct[bcidx].begin(), bct[bcidx].end());

    for(auto& a : ansbuf){
        std::cout << (int)a.size();
        for(auto v : a) std::cout << ' ' << v;
        std::cout << '\n';
    }
    return 0;
}


struct ios_do_not_sync{
    ios_do_not_sync(){
        std::ios::sync_with_stdio(false);
        std::cin.tie(nullptr);
    }
} ios_do_not_sync_instance;
