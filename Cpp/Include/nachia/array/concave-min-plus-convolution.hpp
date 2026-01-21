#pragma once
#include "../array/li-ciao-tree-flexible.hpp"
#include <vector>
#include <algorithm>
#include <utility>

namespace nachia {

    template<class Elem>
    std::vector<std::pair<Elem, int>> MinPlusConvolution_AIsConcave(
        const std::vector<Elem>& A,
        const std::vector<Elem>& B,
        Elem Inf
    ){
        using namespace std;
        int N = (int)A.size();
        int M = (int)B.size();
        std::vector<std::pair<Elem, int>> C(N+M-1, {Inf,-1});
        for(int s=0; s<M; s+=N+1){
            int n = (M-s <= N) ? M-s : (N+1);
            auto ds1 = nachia::LiChaoTreeFlexible(N, 0,
                [&](int a, int b) -> Elem {
                    if(b < a) return -Inf - a;
                    return A[b-a] + B[s+a];
                });
            for(int i=0; i<N; i++){
                if(i+s<M) ds1.addLine(i);
                int k = ds1.minFunc(i);
                Elem fk = A[i-k] + B[s+k];
                if(fk < C[s+i].first) C[s+i] = {fk, i-k};
            }
            auto ds2 = nachia::LiChaoTreeFlexible(n-1, n-1,
                [&](int a, int b) -> Elem {
                    b += 1;
                    if(a < b) return -Inf + a;
                    return A[N-1-(a-b)] + B[s+a];
                });
            for(int i=n-1; i>=1; i--){
                ds2.addLine(i);
                int k = ds2.minFunc(i-1);
                int p = s + (N-1) + i;
                Elem fk = A[p-s-k] + B[s+k];
                if(fk < C[p].first) C[p] = {fk, p-s-k};
            }
        }
        return C;
    }

} // namespace nachia
