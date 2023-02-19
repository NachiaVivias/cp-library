#pragma once
#include <algorithm>
#include "../array/csr-array.hpp"

namespace nachia{

std::vector<CsrArray<int>> EnumeratePartitions(int n){
    std::vector<std::vector<int>> lis(n+1), sep(n+1);
    lis[0] = {}; sep[0] = {0,0};
    for(int m=1; m<=n; m++){
        std::vector<int> lism, sepm = {0};
        for(int k=0; k<m; k++){
            auto lisk = lis[k].begin();
            auto sepk = sep[k].begin();
            for(int prei=0; prei+1<(int)sep[k].size(); prei++) if(sepk[prei+1] - sepk[prei] <= m-k){
                sepm.push_back(sepm.back() + m-k);
                lism.resize(sepm.back());
                std::copy(lisk + sepk[prei], lisk + sepk[prei+1], lism.end() - (m-k));
            }
        }
        for(int& a : lism) a++;
        lis[m] = std::move(lism);
        sep[m] = std::move(sepm);
    }
    std::vector<CsrArray<int>> res(n+1);
    for(int i=0; i<=n; i++) res[i] = CsrArray<int>::FromRaw(std::move(lis[i]), std::move(sep[i]));
    return res;
}

} // namespace nachia
