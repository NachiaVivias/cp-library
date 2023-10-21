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

template<class Elem>
void SumForCoprimeIndex(std::vector<Elem>& f){
    if((int)f.size() <= 1) return;
    Elem q = f[1];
    for(int i=2; i<(int)f.size(); i++) q += f[i];
    std::vector<int> F(f.size()); F[1] = -1;
    DivisorMobius(F);
    DivisorReversedZeta(f);
    f[1] -= f[1];
    Elem t = f[1];
    for(int i=2; i<(int)f.size(); i++){
        if(F[i] == 0) f[i] = f[1];
        if(F[i] == -1){ t = f[1]; t -= f[i]; f[i] = t; }
    }
    DivisorZeta(f);
    for(int i=1; i<(int)f.size(); i++){ t = q; t -= f[i]; f[i] = t; }
}

} // namespace nachia
