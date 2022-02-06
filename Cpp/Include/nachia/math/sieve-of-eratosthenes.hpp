
#include <vector>
#include <algorithm>


namespace nachia{

namespace sieve_of_eratosthenes_internal{
    std::vector<bool> isprime = { false, false };

    void CalcIsPrime(int z){
        if((int)isprime.size() < z+1){
            int new_z = isprime.size();
            while(new_z < z+1) new_z *= 2;
            z = new_z-1;
            isprime.resize(z+1, true);
            for(int i=2; i*i<=z; i++) if(isprime[i]){
                for(int j=i*i; j<=z; j+=i) isprime[j] = false;
            }
        }
    }
}

namespace sieve_of_eratosthenes_internal{
    std::vector<int> prime_list;
    int prime_list_max = 1;

    void CalcPrimeList(int z){
        while((int)prime_list.size() < z){
            if((int)isprime.size() == prime_list_max + 1) CalcIsPrime(prime_list_max + 1);
            for(int p=prime_list_max+1; p<(int)isprime.size(); p++){
                if(isprime[p]) prime_list.push_back(p);
            }
            prime_list_max = isprime.size() - 1;
        }
    }
    
    void CalcPrimeListUntil(int z){
        if(prime_list_max < z){
            CalcIsPrime(z);
            for(int p=prime_list_max+1; p<(int)isprime.size()-1; p++){
                if(isprime[p]) prime_list.push_back(p);
            }
            prime_list_max = isprime.size() - 1;
        }
    }

}


bool IsprimeBySieve(int n){
    using namespace sieve_of_eratosthenes_internal;
    CalcIsPrime(n);
    return isprime[n];
}

int NthPrimeBySieve(int n){
    using namespace sieve_of_eratosthenes_internal;
    CalcPrimeList(n);
    return prime_list[n];
}

int PrimeCountingBySieve(int n){
    using namespace sieve_of_eratosthenes_internal;
    CalcPrimeListUntil(n);
    auto res = ::std::upper_bound(prime_list.begin(), prime_list.end(), n) - prime_list.begin();
    return (int)res;
}

}
