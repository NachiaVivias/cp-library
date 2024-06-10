#pragma once
#include <vector>

namespace nachia{

template<class Modint>
class Comb{
private:
    std::vector<Modint> F;
    std::vector<Modint> iF;
public:
    void extend(int newN){
        int prevN = (int)F.size() - 1;
        if(prevN >= newN) return;
        F.resize(newN+1);
        iF.resize(newN+1);
        for(int i=prevN+1; i<=newN; i++) F[i] = F[i-1] * Modint::raw(i);
        iF[newN] = F[newN].inv();
        for(int i=newN; i>prevN; i--) iF[i-1] = iF[i] * Modint::raw(i);
    }
    Comb(int n = 1){
        F.assign(2, Modint(1));
        iF.assign(2, Modint(1));
        extend(n);
    }
    Modint factorial(int n) const { return F[n]; }
    Modint invFactorial(int n) const { return iF[n]; }
    Modint invOf(int n) const { return iF[n] * F[n-1]; }
    Modint comb(int n, int r) const {
        if(n < 0 || n < r || r < 0) return Modint(0);
        return F[n] * iF[r] * iF[n-r];
    }
    Modint invComb(int n, int r) const {
        if(n < 0 || n < r || r < 0) return Modint(0);
        return iF[n] * F[r] * F[n-r];
    }
    Modint perm(int n, int r) const {
        if(n < 0 || n < r || r < 0) return Modint(0);
        return F[n] * iF[n-r];
    }
    Modint invPerm(int n, int r) const {
        if(n < 0 || n < r || r < 0) return Modint(0);
        return iF[n] * F[n-r];
    }
    Modint operator()(int n, int r) const { return comb(n,r); }
};

} // namespace nachia
