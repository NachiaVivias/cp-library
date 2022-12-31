#pragma once

#include <vector>
#include <cassert>

#include "../math/prime-sieve-explicit.hpp"

namespace nachia{

template<class Elem>
void DivisorZeta(std::vector<Elem>& a){
    int n = a.size() - 1;
    for(int d=2; d<=n; d++) if(IsprimeExplicit(d)) for(int i=1; i*d<=n; i++) a[i*d] += a[i];
}

template<class Elem>
void DivisorReversedZeta(std::vector<Elem>& a){
    int n = a.size() - 1;
    for(int d=2; d<=n; d++) if(IsprimeExplicit(d)) for(int i=n/d; i>=1; i--) a[i] += a[i*d];
}

template<class Elem>
void DivisorMobius(std::vector<Elem>& a){
    int n = a.size() - 1;
    for(int d=2; d<=n; d++) if(IsprimeExplicit(d)) for(int i=n/d; i>=1; i--) a[i*d] -= a[i];
}

template<class Elem>
void DivisorReversedMobius(std::vector<Elem>& a){
    int n = a.size() - 1;
    for(int d=2; d<=n; d++) if(IsprimeExplicit(d)) for(int i=1; i*d<=n; i++) a[i] -= a[i*d];
}

template<class Elem>
std::vector<Elem> GcdConvolution(std::vector<Elem> a, std::vector<Elem> b){
    assert(a.size() == b.size());
    assert(1 <= a.size());
    DivisorReversedZeta(a);
    DivisorReversedZeta(b);
    for(int i=1; i<(int)a.size(); i++) a[i] *= b[i];
    DivisorReversedMobius(a);
    return a;
}

template<class Elem>
std::vector<Elem> LcmConvolution(std::vector<Elem> a, std::vector<Elem> b){
    assert(a.size() == b.size());
    assert(1 <= a.size());
    DivisorZeta(a);
    DivisorZeta(b);
    for(int i=1; i<(int)a.size(); i++) a[i] *= b[i];
    DivisorMobius(a);
    return a;
}

} // namespace nachia
