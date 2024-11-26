#pragma once
#include <vector>
#include <utility>
#include <algorithm>
#include "../array/wavelet-matrix.hpp"

namespace nachia{

struct RangeLis {
private:
    int n;
    WaveletMatrix ds;
    using VectorIter = std::vector<int>::iterator;
    struct Split {
        std::vector<int> I;
        std::vector<int> valL;
        std::vector<int> valR;
    };
    static Split SplitIndex(VectorIter A, int n, int m){
        Split res;
        res.I.resize(n);
        res.valL.resize(m);
        res.valR.resize(n-m);
        for(int i=0; i<m; i++) res.I[A[i]] += 1;
        for(int i=0; i<n-1; i++) res.I[i+1] += res.I[i];
        for(int i=0; i<m; i++){
            int a = A[i];
            A[i] = res.I[a] - 1;
            res.valL[A[i]] = a;
        }
        for(int i=m; i<n; i++){
            int a = A[i];
            A[i] = a - res.I[a];
            res.valR[A[i]] = a;
        }
        return res;
    }
    static std::vector<int> CertainOperator(int n, VectorIter a, VectorIter b){
        if(n == 1) return {0};
        int m = n / 2;
        auto [AI, AvalL, AvalR] = SplitIndex(a, n, m);
        auto [BI, BvalL, BvalR] = SplitIndex(b, n, m);
        auto resL = CertainOperator(m, a, b);
        auto resR = CertainOperator(n-m, a+m, b+m);

        std::vector<int> depV(n);
        std::vector<int> depH(n);
        for(int i=0; i<m; i++){
            depH[AvalL[i]] = BvalL[resL[i]];
            depV[BvalL[resL[i]]] = AvalL[i];
        }
        for(int i=0; i<n-m; i++){
            depH[AvalR[i]] = BvalR[resR[i]] - (n+1) + 1;
            depV[BvalR[resR[i]]] = AvalR[i] - (n+1) + 1;
        }
        std::vector<int> res(n, -1);
        int xi = n;
        for(int yi=0; yi<=n; yi++){
            while(0 < xi){
                if(depV[xi-1] <= yi-(n+1) || yi <= depV[xi-1]) break;
                xi--;
                if(0 <= depV[xi] && depV[xi] <= yi){
                    res[depV[xi]] = xi;
                }
            }
            if(yi != n){
                if(depH[yi] <= xi-(n+1) || xi <= depH[yi]){
                    xi--; res[yi] = xi;
                } else {
                    if(depH[yi] < 0 && xi-(n+1) <= depH[yi]){
                        res[yi] = depH[yi]+(n+1)-1;
                    }
                }
            }
        }
        return res;
    }
public:
    static std::vector<int> MakeTableIn(
        VectorIter A, int n
    ){
        if(n == 1) return { 0, 1 };
        int m = n/2;
        auto [I,valL,valR] = SplitIndex(A, n, m);
        std::vector<int> res(n*2, -1);
        std::vector<int> mapL(n);
        std::vector<int> opL(n); {
            auto BL = MakeTableIn(A, m);
            int j = 0;
            int k = 0;
            for(int i=0; i<m*2; i++){
                int src = i < m ? n - m + i : n + valL[i-m];
                while(k < n-m && valR[k] < src - n){
                    mapL[j] = n + valR[k];
                    opL[j++] = valR[k++];
                }
                if(BL[i] < m){
                    mapL[j] = src;
                    opL[j++] = valL[BL[i]];
                } else {
                    res[src] = (n-m) * 2 + BL[i];
                }
            }
            while(k < n-m){
                mapL[j] = n + valR[k];
                opL[j++] = valR[k++];
            }
        }
        std::vector<int> mapR(n);
        std::vector<int> opR(n); {
            auto BR = MakeTableIn(A+m, n-m);
            std::vector<int> mapinv(n+n-m, 1);
            for(int i=0; i<n-m; i++){
                int dest = (BR[i] < n - m) ? valR[BR[i]] : (m + BR[i]);
                res[i] = dest;
                mapinv[dest] = 0;
            }
            mapinv[0] -= 1;
            for(int i=1; i<n+n-m; i++) mapinv[i] += mapinv[i-1];
            for(int i=n-m; i<(n-m)*2; i++){
                int dest = (BR[i] < n - m) ? valR[BR[i]] : (m + BR[i]);
                opR[valR[i-(n-m)]] = mapinv[dest];
                mapR[mapinv[dest]] = dest;
            }
            for(int i=0; i<m; i++){
                int dest = mapinv[valL[i]];
                opR[valL[i]] = dest;
                mapR[dest] = valL[i];
            }
        }
        std::vector<int> opLInv(n);
        for(int i=0; i<n; i++) opLInv[opL[i]] = i;
        auto mid = CertainOperator(n, opLInv.begin(), opR.begin());
        for(int i=0; i<n; i++) res[mapL[i]] = mapR[mid[i]];
        return res;
    }
    static std::vector<int> MakeTable(
        std::vector<int> A
    ){
        int n = A.size();
        auto B = MakeTableIn(A.begin(), n);
        std::vector<int> res(n);
        for(int i=0; i<n*2; i++) if(B[i] < n) res[B[i]] = std::max(0, i-n+1);
        return res;
    }
    template<class Elem>
    static std::vector<int> InterpretAsPermutation(
        const std::vector<Elem>& seq
    ){
        int n = int(seq.size());
        std::vector<int> I(n);
        for(int i=0; i<n; i++) I[i] = n-1-i;
        std::stable_sort(I.begin(), I.end(), [&](int l, int r){ return seq[l] < seq[r]; });
        return I;
    }
    RangeLis() : n(0) {}
    template<class Elem>
    RangeLis(const std::vector<Elem>& seq)
        : n(int(seq.size()))
        , ds(n, MakeTable(InterpretAsPermutation(seq)))
    {}
    int lis(int l, int r){
        if(l == r) return 0;
        return ds.countRange(l, r, l+1);
    }
};

} // namespace nachia
