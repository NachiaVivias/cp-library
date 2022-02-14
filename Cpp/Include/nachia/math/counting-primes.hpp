#pragma once

#include <vector>
#include <utility>

namespace nachia{

long long CountingPrimes(long long maxval){
    using i64 = long long;
    i64 n = maxval;
    if(n <= 1) return 0;

    i64 sqrtn = 0; while(sqrtn * sqrtn <= n) sqrtn++; sqrtn--;
    
    std::vector<i64> prefix_sum_fairy(sqrtn+1, 0);
    for(i64 i=1; i<=sqrtn; i++) prefix_sum_fairy[i] = i-1;

    std::vector<i64> prefix_sum_devil(sqrtn+1, 0);
    for(i64 i=1; i<=sqrtn; i++) prefix_sum_devil[i] = n/i-1;

    for(i64 p=2; p<=sqrtn; p++){
        i64 prime_count_p = prefix_sum_fairy[p];
        i64 prime_count_p_minus1 = prefix_sum_fairy[p-1];
        if(prime_count_p == prime_count_p_minus1) continue;
        for(i64 devil_id = 1; devil_id <= sqrtn; devil_id++){
            if(devil_id * p <= sqrtn){
                prefix_sum_devil[devil_id] -= prefix_sum_devil[devil_id * p] - prime_count_p_minus1;
            }
            else{
                i64 tg_fairy = n / (devil_id * p);
                if(tg_fairy < p) break;
                prefix_sum_devil[devil_id] -= prefix_sum_fairy[tg_fairy] - prime_count_p_minus1;
            }
        }
        for(i64 fairy_id = sqrtn/p; fairy_id >= p; fairy_id--){
            i64 dc = prefix_sum_fairy[fairy_id] - prime_count_p_minus1;
            i64 max_tg = std::min(fairy_id * p + p - 1, sqrtn);
            for(i64 tg_fairy = fairy_id * p; tg_fairy <= max_tg; tg_fairy++) prefix_sum_fairy[tg_fairy] -= dc;
        }
    }

    return prefix_sum_devil[1];
}

} // namespace nachia
