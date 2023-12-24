#pragma once
#include <vector>
#include <algorithm>

namespace nachia{

std::vector<int> SubsetSumHalfBruteforce(long long X, std::vector<long long> A){
    using i64 = long long;
    i64 sum_min = 0, sum_max = 0;
    for(i64 a : A){
        if(a < 0) sum_min += a;
        else sum_max += a;
    }
    if(sum_min > X || X > sum_max) return {-1};
    auto SumSort = [](std::vector<i64> A) {
        std::vector<std::pair<i64, int>> res = {{0,0}};
        for(std::size_t i=0; i<A.size(); i++){
            std::vector<std::pair<i64, int>> t(res.size()), u(res.size() * 2);
            for(int j=0; j<(1<<i); j++) t[j] = { res[j].first + A[i], res[j].second | (1 << i) };
            std::merge(res.begin(), res.end(), t.begin(), t.end(), u.begin());
            std::swap(res, u);
        }
        return res;
    };
    int n = A.size();
    auto T = SumSort(std::vector<i64>(A.begin(), A.begin() + n/2));
    auto U = SumSort(std::vector<i64>(A.begin() + n/2, A.end()));
    int up = 0;
    for(int tp=(int)T.size()-1; tp>=0; tp--){
        i64 t = X - T[tp].first;
        while(up < (int)U.size() && U[up].first < t) up++;
        if((int)U.size() <= up) break;
        if(U[up].first != t) continue;
        int ti = T[tp].second;
        int ui = U[up].second;
        std::vector<int> ans;
        for(int f=0; f<n/2; f++){
            ans.push_back(ti % 2);
            ti /= 2;
        }
        for(int f=n/2; f<n; f++){
            ans.push_back(ui % 2);
            ui /= 2;
        }
        return ans;
    }
    return {-1};
}

} // namespace nachia
