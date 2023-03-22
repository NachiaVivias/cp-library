#pragma once
#include "../graph/graph.hpp"
#include <vector>
#include <algorithm>

namespace nachia{

template<class T>
nachia::Graph CartesianTree(const std::vector<T>& A){
    int n = A.size();
    std::vector<int> st(n);
    nachia::Graph res(n, false, n-1);
    int stp = -1, resp = n-1;
    for(int i=n-1; i>=0; i--){
        int c = -1;
        while(stp >= 0 && A[i] < A[st[stp]]){
            int t = st[stp--];
            if(0 <= c) res[--resp] = { t, c };
            c = t;
        }
        if(c >= 0) res[--resp] = { i, c };
        st[++stp] = i;
    }
    for(int i=stp-1; i>=0; i--) res[--resp] = { st[i], st[i+1] };
    return res;
}

} // namespace nachia
