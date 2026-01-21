#pragma once
#include <vector>
#include <utility>

namespace nachia {

    template<class Elem>
    std::vector<std::pair<Elem, int>> MinPlusConvolution_AIsConvex(
        const std::vector<Elem>& A,
        const std::vector<Elem>& B,
        Elem Inf
    ){
        int n = A.size();
        int m = B.size();
        int z = n + m - 1;
        std::vector<std::pair<Elem, int>> c(z, {Inf,-1});
        std::vector<int> idx(z+1);
        c[0] = { A[0] + B[0], 0 };
        idx.back() = m-1;
        int d = 1; while(d < z) d *= 2;
        for(int q=d/2; q>0; q/=2){
            for(int h=q; h<z; h+=q*2){
                int l = h-q, r = std::min(h+q, z);
                idx[h] = idx[l];
                for(int t=idx[l]; t<=idx[r]; t++){
                    if(t<=h && h-t<n && B[t] + A[h-t] < c[h].first){
                        c[h] = { B[t] + A[h-t], h-t };
                        idx[h] = t;
                    }
                }
            }
        }
        return c;
    }

} // namespace nachia
