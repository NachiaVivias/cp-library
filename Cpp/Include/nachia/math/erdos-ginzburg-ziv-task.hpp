#pragma once
#include <vector>
#include <algorithm>
#include <utility>

namespace nachia {

    std::vector<int> ErdosGinzburgZivTask(int N, std::vector<int> A){
        if(N == 1){ return { A[0] }; }
        for(int p=2; p*p<=N; p++) if(N%p == 0){
            int n = N / p;
            std::vector<int> rem(N*2-1), hold(p*(n*2-1)), B(n*2-1);
            for(int i=0; i<N*2-1; i++) rem[i] = i;
            for(int k=0; k<n*2-1; k++){
                std::vector<int> sub(p*2-1);
                for(int i=0; i<p*2-1; i++) sub[i] = A[rem[i]];
                std::vector<int> subans = ErdosGinzburgZivTask(p, sub);
                for(int i=0; i<p; i++) hold[k*p+i] = std::exchange(rem[subans[i]], -1);
                for(int i=0; i<p; i++) B[k] = (B[k] + A[hold[k*p+i]]) % N;
                for(int i=0; i<p*2-1 && i<int(rem.size()); i++) if(rem[i] < 0){
                    std::swap(rem[i--], rem.back());
                    rem.pop_back();
                }
            }
            for(int& b : B) b /= p;
            std::vector<int> subans = ErdosGinzburgZivTask(n, B);
            std::vector<int> res(N);
            for(int k=0; k<n; k++) for(int i=0; i<p; i++) res[k*p+i] = hold[subans[k]*p+i];
            return res;
        }
        for(int& a : A) a %= N;
        std::vector<int> I(N*2-1);
        for(int i=0; i<N*2-1; i++) I[i] = i;
        std::sort(I.begin(), I.end(), [&](int l, int r){ return A[l] < A[r]; });
        for(int p=0; p<N; p++) if(A[I[p]] == A[I[p+N-1]]) return std::vector<int>(I.begin() + p, I.begin() + p + N);
        auto mulMod = [N](int a, int b) -> int { return (long long)a * b % N; };
        std::vector<int> inv(N);
        inv[1] = 1;
        for(int a=2; a<N; a++) inv[a] = N - mulMod(N / a, inv[N % a]);
        std::vector<std::pair<int,int>> dp(N, {-1,-1});
        int unlit = 1;
        for(int i=0; i<N-1; i++){
            while(dp[unlit].first >= 0) unlit++;
            int w = A[I[i+N]] - A[I[i]];
            int ok = 0, ng = mulMod(unlit, inv[w]);
            while(ok + 1 < ng){
                int t = (ok + ng) / 2;
                if(dp[mulMod(w, t)].first >= 0) ok = t; else ng = t;
            }
            dp[mulMod(w, ng)] = { i, mulMod(w, ok) };
        }
        int tg = 0;
        for(int i=0; i<N; i++) if((tg += N - A[I[i]]) >= N) tg -= N;
        std::vector<int> ans(N);
        for(int i=0; i<N; i++) ans[i] = i;
        while(tg){
            ans[dp[tg].first] += N;
            tg = dp[tg].second;
        }
        for(int& a : ans) a = I[a];
        return ans;
    }

} // namespace nachia
