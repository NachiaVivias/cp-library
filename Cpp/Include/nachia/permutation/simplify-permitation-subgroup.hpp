#pragma once
#include <vector>
#include <algorithm>

namespace nachia{

// res.size() = n
// res[a][*].size() = (force_size_n ? n : (a+1))
// res[a][*][a] distinct
std::vector<std::vector<std::vector<int>>> SimplifyPermutationSubgroup(
    int n,
    std::vector<std::vector<int>> perm,
    bool force_size_n = true
){
    using VV = std::vector<std::vector<int>>;
    std::vector<VV> elim(n);
    for(int i=0; i<n; i++) elim[i].resize(i);
    auto elim_insert = [&](std::vector<int> p, int m){
        auto nx = p;
        for(int a=m-1; a>=1; a--) if(p[a] != a){
            auto& tg = elim[a][p[a]];
            if(tg.empty()){ std::swap(tg, p); break; }
            for(int t=0; t<m; t++) nx[tg[t]] = t;
            for(int t=0; t<m; t++) p[t] = nx[p[t]];
        }
    };
    for(auto& p : perm) elim_insert(std::move(p), n);
    std::vector<VV> res(n);
    for(int f=n-1; f>=1; f--){
        VV orb(f+1);
        std::vector<int> bfs;
        bfs.push_back(f);
        orb[f].resize(f+1);
        for(int i=0; i<=f; i++) orb[f][i] = i;
        for(int z=0; z<int(bfs.size()); z++){
            int s = bfs[z];
            for(int a=s; a<=f; a++) for(auto& pm : elim[a]){
                if(!pm.empty() && orb[pm[s]].empty()){
                    std::vector<int> nx(f+1);
                    for(int i=0; i<=f; i++) nx[i] = pm[orb[s][i]];
                    orb[pm[s]] = std::move(nx);
                    bfs.push_back(pm[s]);
                }
            }
        }
        VV iorb(f+1);
        for(int a=0; a<=f; a++) if(!orb[a].empty()){
            iorb[a].resize(f+1);
            for(int i=0; i<=f; i++) iorb[a][orb[a][i]] = i;
        }
        std::vector<VV> elimnx(f+1);
        for(int d=0; d<=f; d++) elimnx[d].resize(d+1);
        std::swap(elim, elimnx);
        for(int a=1; a<=f; a++) for(auto& p : elimnx[a]) if(!p.empty()){
            for(int o : bfs){
                std::vector<int> q(f);
                for(int i=0; i<f; i++) q[i] = iorb[p[o]][p[orb[o][i]]];
                elim_insert(std::move(q), f);
            }
        }
        for(int a : bfs){
            if(force_size_n){
                res[f].push_back(std::vector<int>(n));
                for(int i=0; i<n; i++) res[f].back()[i] = i;
                for(int i=0; i<=f; i++) res[f].back()[i] = orb[a][f];
            } else {
                res[f].push_back(std::move(orb[a]));
            }
        }
    }
    return res;
}

} // namespace nachia
