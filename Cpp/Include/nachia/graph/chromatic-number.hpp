#pragma once
#include <vector>
#include <utility>
#include <cassert>

namespace nachia{

namespace chromatic_number_internal{
    int parity(unsigned int b){
    #if defined __GNUC__
        return __builtin_parity(b);
    #else
        b ^= b >> 16;
        b ^= b >> 8;
        b ^= b >> 4;
        b ^= b >> 2;
        b ^= b >> 1;
        return (int)(b & 1);
    #endif
    }
}

int ChromaticNumber(std::vector<std::vector<int>> adjacency_matrix){
    using u32 = unsigned int;
    using u64 = unsigned long long;
    std::vector<std::vector<int>> D = std::move(adjacency_matrix);
    u32 n = D.size();
    u32 nn = 1 << n;
    std::vector<u32> E(n,nn-1);
    for(int i=0; i<n; i++) for(int j=0; j<n; j++) if(i!=j) if(D[i][j] == 1) E[i] -= (1<<j);
    std::vector<u32> A(nn>>1,0); A[0] = 1;
    for(int d=0; d<n-1; d++) for(u32 i=0; i<(1<<d); i++) A[i|(1<<d)] = A[i] + A[i&E[d]];
    std::vector<u32> T(nn>>1,0); T[0] = 1;
    for(u32 d=0; d<n-1; d++) for(u32 i=0; i<(1<<d); i++) T[i|(1<<d)] = T[i] + ((E[d] & (nn>>1)) ? T[i&E[d]] : 0);

    bool graph_empty = true;
    for(auto e : E) if(e != (nn-1)) graph_empty = false;
    if(graph_empty) return 1;

    for(int d=1; d<n; d++){
        u32 h = 1 << (d-1);
        std::vector<u64> P(d+2), Q(d+2);
        for(u32 p=0; p<(nn>>1); p+=(1<<d)){
            auto i = T.begin() + p;
            u32 xa = A[p], xb = A[p+h];
            u64 a = 0, b = 0;
            for(u32 j=0; j<d; j++){
                a += (u64)i[h+j] * xb;
                b += (u64)i[j] * xa;
                i[j] = (u32)(a - b);
                if((a >> 32) < (b >> 32)) b += (u64)1 << 32;
                a >>= 32; b >>= 32;
            }
            i[d] = (u32)(a - b);
            if(chromatic_number_internal::parity(p)){
                for(u32 j=0; j<=d; j++) Q[j] += i[j];
            } else {
                for(u32 j=0; j<=d; j++) P[j] += i[j];
            }
        }
        for(int j=0; j<=d; j++){
            P[j+1] += P[j] >> 32;
            P[j] -= (P[j] >> 32) << 32;
            Q[j+1] += Q[j] >> 32;
            Q[j] -= (Q[j] >> 32) << 32;
        }
        if(P != Q) return d + 1;
    }
    return -1;
}

} // namespace nachia
