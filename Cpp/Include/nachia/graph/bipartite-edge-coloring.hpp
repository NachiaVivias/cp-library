#pragma once
#include <vector>
#include <utility>
#include <algorithm>

namespace nachia {

struct RegularBipartiteGraph {
    int n;
    int k;
    std::vector<std::pair<int, int>> edges;
};

RegularBipartiteGraph BipartiteRegularizeEdgeColorEquivalent(
    int n1,
    int n2,
    std::vector<std::pair<int,int>> edges
){
    std::vector<int> ind1(n1);
    std::vector<int> ind2(n2);
    for(auto [u,v] : edges){ ind1[u]++; ind2[v]++; }
    int k = std::max(
        *std::max_element(ind1.begin(), ind1.end()),
        *std::max_element(ind2.begin(), ind2.end()));
    std::vector<int> map1(n1);
    std::vector<int> map2(n2);
    std::vector<int> indx1(std::max(n1, n2));
    std::vector<int> indx2(std::max(n1, n2));
    indx1[0] += ind1[0];
    for(int i=1; i<n1; i++){
        map1[i] = map1[i-1];
        if(indx1[map1[i]] + ind1[i] > k) map1[i]++;
        indx1[map1[i]] += ind1[i];
    }
    indx2[0] += ind2[0];
    for(int i=1; i<n2; i++){
        map2[i] = map2[i-1];
        if(indx2[map2[i]] + ind2[i] > k) map2[i]++;
        indx2[map2[i]] += ind2[i];
    }
    int n = std::max(map1.back() + 1, map2.back() + 1);
    RegularBipartiteGraph res = { n, k, std::vector<std::pair<int,int>>(n*k) };
    for(int i=0; i<int(edges.size()); i++){
        res.edges[i] = { map1[edges[i].first], map2[edges[i].second] };
    }
    int s1 = 0;
    int s2 = 0;
    for(int i=int(edges.size()); i<n*k; i++){
        while(indx1[s1] == k) s1++;
        while(indx2[s2] == k) s2++;
        res.edges[i] = { s1, s2 };
        indx1[s1]++; indx2[s2]++;
    }
    return res;
}

std::vector<int> RegularBipartiteEdgeColor(const RegularBipartiteGraph& g){
    int n = g.n * 2;
    std::vector<int> inci(n * g.k);
    int m = g.n * g.k;
    std::vector<int> xedge(m); {
        std::vector<int> head(n);
        for(int e=0; e<m; e++){
            auto [u,v] = g.edges[e];
            inci[g.k*(u*2+0) + head[u*2+0]++] = e;
            inci[g.k*(v*2+1) + head[v*2+1]++] = e;
            xedge[e] = (u*2+0) ^ (v*2+1);
        }
    }
    std::vector<int> flag_e(m);
    int nx_flag = 0;
    auto euler_splitting = [&](
        std::vector<int> pl,
        std::vector<int> pr
    ) -> std::vector<int> {
        nx_flag++;
        for(int sp=0; sp<n; sp++){
            int v = sp;
            while(true){
                if(pl[v] == pr[v]){
                    if(sp == v) break;
                    v ^= 1;
                    continue;
                }
                int e = inci[pl[v]++];
                int w = v;
                if(flag_e[e] != nx_flag){
                    flag_e[e] = nx_flag;
                    w = v ^ xedge[e];
                }
                if(w % 2 == 0) std::swap(inci[--pl[v]], inci[--pr[v]]);
                v = w;
            }
        }
        return pl;
    };
    auto swap_group = [&](
        const std::vector<int>& el,
        std::vector<int>& em,
        const std::vector<int>& er
    ) -> void {
        for(int i=0; i<n; i++){
            int len = std::min(em[i] - el[i], er[i] - em[i]);
            std::swap_ranges(
                inci.begin() + el[i],
                inci.begin() + (el[i] + len),
                inci.begin() + (er[i] - len));
            em[i] = er[i] + el[i] - em[i];
        }
    };
    auto take_matching = [&](
        int s, int d
    ) -> void {
        std::vector<int> pl(n);
        std::vector<int> pr(n);
        for(int i=0; i<n; i++) pl[i] = i * g.k + s;
        for(int i=0; i<n; i++) pr[i] = i * g.k + s + d;
        std::vector<int> pm = pr;
        int md = 1; while(md < n/2*d) md *= 2;
        int alpha = md / d;
        while(alpha % 2 == 0){ alpha /= 2; md /= 2; }
        for(int w=1; w<md; w*=2){
            if(alpha & w){
                auto plm = euler_splitting(pl, pm);
                int count_edges = 0;
                for(int i=0; i<n; i+=2) count_edges += pm[i] + pl[i] - plm[i] * 2;
                if(count_edges < 0) swap_group(pl, plm, pm);
                std::swap(pm, plm);
            } else {
                auto pmr = euler_splitting(pm, pr);
                int count_edges = 0;
                for(int i=0; i<n; i+=2) count_edges += pr[i] + pm[i] - pmr[i] * 2;
                if(count_edges < 0) swap_group(pm, pmr, pr);
                std::swap(pm, pmr);
            }
        }
    };
    auto part_color = [&](
        auto& rec,
        int s, int d
    ) -> void {
        if(d <= 1) return;
        int d2 = d;
        if(d2 % 2 == 1){
            if(s+d2 < g.k) d2++;
            else{ take_matching(s, d2); d2--; }
        }
        std::vector<int> pl(n);
        std::vector<int> pr(n);
        for(int i=0; i<n; i++) pl[i] = i * g.k + s;
        for(int i=0; i<n; i++) pr[i] = i * g.k + s + d2;
        euler_splitting(std::move(pl), std::move(pr));
        rec(rec, s+d2/2, d2/2);
        rec(rec, s, d2/2);
    };
    part_color(part_color, 0, g.k);
    std::vector<int> ans(m);
    for(int i=0; i<n; i+=2) for(int j=0; j<g.k; j++) ans[inci[i*g.k+j]] = j;
    return ans;
}

std::vector<int> BipartiteEdgeColor(
    int n1,
    int n2,
    std::vector<std::pair<int,int>> edges
){
    int m = edges.size();
    auto regularized = BipartiteRegularizeEdgeColorEquivalent(n1, n2, std::move(edges));
    auto ans = RegularBipartiteEdgeColor(regularized);
    ans.resize(m);
    return ans;
}

} // namespace nachia
