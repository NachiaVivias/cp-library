#pragma once
#include <vector>
#include <algorithm>

namespace nachia{

template<class E>
std::vector<E> SpsPowerProjection(int n, const std::vector<E>& A, const std::vector<E>& W, int m, bool exponential = false){
    const E a0 = A[0];

    using iter = typename std::vector<E>::iterator;
    struct {
        std::vector<int> Chi;
        void init(int n){
            Chi.resize(1<<n);
            for(int i=1; i<(1<<n); i++) Chi[i] = Chi[i-(i&-i)] + 1;
        }
        void zeta(int n, typename std::vector<E>::const_iterator a, iter r){
            int N = n + 1;
            auto z = E(0);
            for(int i=0; i<N<<n; i++) r[i] = z;
            for(int i=0; i<1<<n; i++) r[Chi[i]+i*N] = a[i];
            for(int w=1; w<=1<<n; w++) for(int d=0; !(w&(1<<d)); d++){
                int W = N * (w-(1<<d)), dd = N<<d;
                for(int i=N * (w-(2<<d)); i<W; i++) r[i+dd] += r[i];
            }
        }
        void comp(int n, iter a, iter r){
            for(int i=0; i<(1<<n); i++){
                std::copy(a, a + n, r);
                a += (n + 1);
                r += n;
            }
        }
        void conv(int n, iter a, iter b){
            int N = n + 1;
            for(int i=0; i<(1<<n); i++){
                int I=i*N;
                std::vector<E> Q(N);
                for(int ja=0; ja<=Chi[i]; ja++) for(int jb=Chi[i]-ja, x=std::min(n-ja, Chi[i]); jb<=x; jb++){
                    Q[ja+jb] += a[ja+I] * b[jb+I];
                }
                std::copy(Q.begin(), Q.end(), a + I);
            }
        }
        void mobius(int n, iter a, iter r){
            int N = n + 1;
            for(int w=1; w<=(1<<n); w++) for(int d=0; !(w&(1<<d)); d++){
                int W = N * (w-(1<<d)), dd = N<<d;
                for(int i=N * (w-(2<<d)); i<W; i++) a[i+dd] -= a[i];
            }
            for(int i=0; i<(1<<n); i++) r[i] = a[Chi[i]+i*N];
        }
    } rz; rz.init(n);

    std::vector<std::vector<E>> zet(n);
    for(int d=0; d<n; d++) zet[d].resize((d+1)<<d);
    for(int i=0; i<n; i++) rz.zeta(i, A.begin() + (1<<i), zet[i].begin());
    
    std::vector<E> res(1<<n);
    std::vector<E> zet2(n << (n-1));
    std::vector<E> p(n+1);
    for(int i=0; i<(1<<n); i++) res[i] = W[i];

    for(int d=n-1; d>=0; d--){
        p[n-1-d] = res[0];
        std::vector<E> buf(1 << d);
        std::vector<E> buf2(1 << d);
        for(int e=d; e>=0; e--){
            std::reverse(res.begin() + (1 << e), res.begin() + (2 << e));
            rz.zeta(e, res.begin() + (1 << e), zet2.begin());
            rz.conv(e, zet2.begin(), zet[e].begin());
            rz.mobius(e, zet2.begin(), buf2.begin());
            std::reverse(buf2.begin(), buf2.begin() + (1 << e));
            for(int i=0; i<(1<<e); i++) buf[i] += buf2[i];
        }
        std::swap(res, buf);
    }
    p[n] = res[0];
    if(!exponential){
        E f = E(1);
        for(int i=1; i<=n; i++) p[i] *= (f *= E(i));
    }
    
    if(a0.val() != 0){
        std::vector<E> comb(n+1, E(1));
        std::vector<E> ans(m);
        E c = 1;
        for(int d=0; d<m; d++){
            for(int i=0; i<=n && i+d<m; i++) ans[i+d] += comb[i] * c * p[i];
            for(int i=0; i<n; i++) comb[i+1] += comb[i];
            c *= a0;
        }
        return ans;
    }
    p.resize(m);
    return p;
}

} // namespace nachia
