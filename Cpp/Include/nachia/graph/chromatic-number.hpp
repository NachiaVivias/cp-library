
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
    u32 n = adjacency_matrix.size();
    assert(1 <= n); assert(n <= 30);
    for(int i=0; i<n; i++) assert(adjacency_matrix[i].size() == 30);
    for(int i=0; i<n; i++) assert(adjacency_matrix[i][i] == 0);
    for(int i=0; i<n; i++) for(int j=0; j<n; j++) assert(adjacency_matrix[i][j] == adjacency_matrix[j][i]);
    u32 nn = 1 << n;
    std::vector<u32> E(n,nn-1);
    for(int i=0; i<n; i++) for(int j=0; j<n; j++) if(i!=j) if(adjacency_matrix[i][j] == 1) E[i] -= (1<<j);
    std::vector<u32> A(nn>>1,0); A[0] = 1;
    for(int d=0; d<n-1; d++) for(int i=0; i<(1<<d); i++) A[i|(1<<d)] = A[i] + A[i&E[d]];
    std::vector<u32> table(nn>>1,0); table[0] = 1;
    for(u32 d=0; d<n-1; d++) for(u32 i=0; i<(1<<d); i++) table[i|(1<<d)] = table[i] + ((E[d] & (nn>>1)) ? table[i&E[d]] : 0);
    bool graph_empty = true;
    for(auto e : E) if(e != (nn-1)) graph_empty = false;
    if(graph_empty) return 1;
    for(int iD = 1; iD < n; iD++){
        u32 biD = 1<<(n-iD);
        u32 biDh = biD>>1;
        for(u32 i=0; i<biD; i++) table[i] *= A[i];
        for(u32 i=0; i<biDh; ++i) table[i|biDh] -= table[i];
        for(u32 d=0; d<n-iD-1; d++) for(u32 i=biDh; i<biD; ++i, i+=i&(1<<d)) table[i|(1<<d)] -= table[i];
        if(table[biD-1] != 0) return iD+1;
        for(u32 i=0; i<biDh; i++) table[i] = table[biDh|i] ? 1 : 0;
        for(u32 d=0; d<n-iD-1; d++) for(u32 i=0; i<biD; ++i, i+=i&(1<<d)) table[i|(1<<d)] += table[i];
    }
    return -1;
}

template<unsigned int MOD>
int ChromaticNumberByMod(std::vector<std::vector<int>> adjacency_matrix){
    using u32 = unsigned int;
    u32 n = adjacency_matrix.size();
    assert(1 <= n); assert(n <= 30);
    assert(((u32)1 << n) < MOD); assert(MOD < (u32)1 << 31);
    for(int i=0; i<n; i++) assert(adjacency_matrix[i].size() == 30);
    for(int i=0; i<n; i++) assert(adjacency_matrix[i][i] == 0);
    for(int i=0; i<n; i++) for(int j=0; j<n; j++) assert(adjacency_matrix[i][j] == adjacency_matrix[j][i]);
    u32 nn = 1 << n;
    std::vector<u32> E(n,nn-1);
    for(u32 i=0; i<n; i++) for(u32 j=0; j<n; j++) if(i!=j) if(adjacency_matrix[i][j] == 1) E[i] -= (1<<j);
    std::vector<u32> A(nn>>1,0); A[0] = 1;
    for(u32 d=0; d<n-1; d++) for(u32 i=0; i<(1<<d); i++) A[i|(1<<d)] = A[i] + A[i&E[d]];
    std::vector<u32> table(nn>>1,0); table[0] = 1;
    for(u32 d=0; d<n-1; d++) for(u32 i=0; i<(1<<d); i++) table[i|(1<<d)] = table[i] + ((E[d] & (nn>>1)) ? table[i&E[d]] : 0);
    for(u32 i=0; i<(nn>>1); i++) table[i] = chromatic_number_internal::parity(i) ? table[i] : (MOD - table[i]);
    bool graph_empty = true;
    for(auto e : E) if(e != (nn-1)) graph_empty = false;
    if(graph_empty) return 1;
    for(u32 iD=1; iD<n; iD++){
        u32 biD = 1<<(n-iD);
        u32 biDh = biD>>1;
        for(u32 i=0; i<biD; i++) table[i] = (unsigned long long)table[i] * A[i] % MOD;
        for(u32 i=0; i<biDh; i++) table[i] += table[i|biDh];
        unsigned long long cond = 0;
        for(u32 i=0; i<biDh; i++) cond += table[i];
        if(cond % MOD != 0) return iD+1;
    }
    return -1;
}

} // namespace nachia
