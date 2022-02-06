
#include <vector>
#include <algorithm>
#include <cassert>
#include <iostream>


namespace nachia{

namespace prime_sieve_explicit_internal{
    std::vector<bool> isprime = { false }; // a[x] := isprime(2x+1)

    void CalcIsPrime(int z){
        if((int)isprime.size() *2+1 < z+1){
            int new_z = isprime.size();
            while(new_z*2+1 < z+1) new_z *= 2;
            z = new_z-1;
            isprime.resize(z+1, true);
            for(int i=1; i*(i+1)*2<=z; i++) if(isprime[i]){
                for(int j=i*(i+1)*2; j<=z; j+=i*2+1) isprime[j] = false;
            }
        }
    }
    
    std::vector<int> prime_list = {2};
    int prime_list_max = 0;

    void CalcPrimeList(int z){
        while((int)prime_list.size() < z){
            if((int)isprime.size() <= prime_list_max + 1) CalcIsPrime(prime_list_max + 1);
            for(int p=prime_list_max+1; p<(int)isprime.size(); p++){
                if(isprime[p]) prime_list.push_back(p*2+1);
            }
            prime_list_max = isprime.size() - 1;
        }
    }
    
    void CalcPrimeListUntil(int z){
        if(prime_list_max < z){
            CalcIsPrime(z);
            for(int p=prime_list_max+1; p<(int)isprime.size()-1; p++){
                if(isprime[p]) prime_list.push_back(p*2+1);
            }
            prime_list_max = isprime.size() - 1;
        }
    }

}


bool IsprimeExplicit(int n){
    using namespace prime_sieve_explicit_internal;
    if(n == 2) return true;
    if(n % 2 == 0) return false;
    CalcIsPrime(n);
    return isprime[(n-1)/2];
}

int NthPrimeExplicit(int n){
    using namespace prime_sieve_explicit_internal;
    CalcPrimeList(n);
    return prime_list[n];
}

int PrimeCountingExplicit(int n){
    using namespace prime_sieve_explicit_internal;
    if(n < 2) return 0;
    CalcPrimeListUntil(n);
    auto res = ::std::upper_bound(prime_list.begin(), prime_list.end(), n) - prime_list.begin();
    return (int)res;
}

// [l, r)
::std::vector<bool> SegmentedSieveExplicit(long long l, long long r){
    assert(0 <= l); assert(l <= r);
    long long d = r - l;
    if(d == 0) return {};
    ::std::vector<bool> res(d, true);
    for(long long p=2; p*p<=r; p++) if(IsprimeExplicit(p)){
        long long il = (l+p-1)/p, ir = (r+p-1)/p;
        if(il <= p) il = p;
        for(long long i=il; i<ir; i++) res[i*p-l] = false;
    }
    if(l < 2) for(long long p=l; p<2 && p<r; p++) res[l-p] = false;
    return res;
}


}
