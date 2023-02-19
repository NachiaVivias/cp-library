#pragma once

#include <vector>
#include <cassert>
#include <algorithm>

namespace nachia{

template<class Iterator>
void EnsurePermutation(Iterator first, Iterator last){
    int n = std::distance(first, last);
    std::vector<int> vis(n, 0);
    for(Iterator i=first; i!=last; i++){
        assert(0 <= *i);
        assert(*i < n);
        assert(vis[*i] == 0);
        vis[*i] = 1;
    }
}

template<class T> std::vector<T> Permute(
    const std::vector<T>& src,
    const std::vector<int>& perm
){
    const bool DEBUG = true;
    int n = src.size();
    if constexpr (DEBUG){
        assert(perm.size() == src.size());
        EnsurePermutation(perm.begin(), perm.end());
    }
    std::vector<T> res;
    res.reserve(n);
    for(int i=0; i<n; i++) res.push_back(src[perm[i]]);
    return res;
}

template<class T> std::vector<T>& PermuteInPlace(
    std::vector<T>& src,
    std::vector<int> perm
){
    const bool DEBUG = true;
    int n = src.size();
    if constexpr (DEBUG){
        assert(perm.size() == src.size());
        EnsurePermutation(perm.begin(), perm.end());
    }
    for(int s=0; s<n; s++){
        int p = s;
        while(perm[p] != s){
            std::swap(src[p], src[perm[p]]);
            std::swap(p, perm[p]);
        }
        perm[p] = p;
    }
    return src;
}

// stable sort
std::vector<int> BucketSortPermutation(
    std::vector<int>::const_iterator first,
    std::vector<int>::const_iterator last,
    int maxVal
){
    const bool DEBUG = true;
    int n = last - first;
    if constexpr (DEBUG){
        for(auto itr = first; itr != last; itr++){
            assert(0 <= *itr);
            assert(*itr <= maxVal);
        }
    }
    std::vector<int> cnt(maxVal+2);
    std::vector<int> res(n);
    for(int i=0; i<n; i++) cnt[first[i]+1]++;
    for(int i=0; i<maxVal; i++) cnt[i+1] += cnt[i];
    for(int i=0; i<n; i++) res[cnt[first[i]]++] = i;
    return res;
}

// stable sort
template<class T, class Mapping>
std::vector<int> BucketSortPermutation(
    typename std::vector<T>::const_iterator first,
    typename std::vector<T>::const_iterator last,
    const Mapping& f,
    int maxVal
){
    std::vector<int> buf(last - first);
    auto bufitr = buf.begin();
    for(auto itr = first; itr != last; itr++, bufitr++) *bufitr = f(*itr);
    return BucketSortPermutation(buf.begin(), buf.end(), maxVal);
}

// stable sort
template<class T, class Mapping>
std::vector<T> BucketSort(
    std::vector<T> src,
    const Mapping& f,
    int maxVal
){
    return PermuteInPlace(src, BucketSortPermutation<T>(src.begin(), src.end(), f, maxVal));
}

// stable sort
template<class Iter, class Mapping>
std::vector<int> BucketSortPermutation(
    Iter first,
    Iter last,
    const Mapping& f,
    int maxVal
){
    std::vector<int> buf(std::distance(first, last));
    auto bufitr = buf.begin();
    for(auto itr = first; itr != last; itr++, bufitr++) *bufitr = f(*itr);
    return BucketSortPermutation(buf.begin(), buf.end(), maxVal);
}

template<class Iter> void PermuteInPlace(
    Iter srcFirst,
    Iter srcLast,
    std::vector<int> perm
){
    const bool DEBUG = true;
    int n = std::distance(srcFirst, srcLast);
    if constexpr (DEBUG){
        assert(perm.size() == (size_t)n);
        EnsurePermutation(perm.begin(), perm.end());
    }
    for(int s=0; s<n; s++){
        int p = s;
        while(perm[p] != s){
            std::swap(srcFirst[p], srcFirst[perm[p]]);
            std::swap(p, perm[p]);
        }
        perm[p] = p;
    }
}

// stable sort
template<class Iter, class Mapping>
void BucketSort(
    Iter destFirst,
    Iter destLast,
    const Mapping& f,
    int maxVal
){
    PermuteInPlace(destFirst, destLast, BucketSortPermutation(destFirst, destLast, f, maxVal));
}

}
