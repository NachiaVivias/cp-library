#pragma once
#include <utility>
#include <algorithm>
#include <cassert>

namespace nachia{

// ax + by = gcd(a,b)
std::pair<long long, long long> ExtGcd(long long a, long long b){
    long long x = 1, y = 0;
    while(b){
        long long u = a / b;
        std::swap(a-=b*u, b);
        std::swap(x-=y*u, y);
    }
    return std::make_pair(x, y);
}

} // namespace nachia
