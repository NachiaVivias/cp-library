#define PROBLEM "https://atcoder.jp/contests/nikkei2019-2-final/tasks/nikkei2019_2_final_d"

#include "../../Include/nachia/tree/ahu-algorithm.hpp"
#include "../../Include/nachia/tree/tree-center.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
 
std::pair<int, int> one_difference(
    const std::vector<int>& a,
    const std::vector<int>& b
){
    std::pair<int,int> res = {-1,-1};
    int maxa = -1;
    for(auto x : a) maxa = std::max(maxa, x);
    for(auto x : b) maxa = std::max(maxa, x);
    std::vector<int> acnt(maxa + 1);
    for(auto x : a) acnt[x]++;
    for(auto x : b) acnt[x]--;
    for(int i=0; i<(int)acnt.size(); i++){
        if(acnt[i] > 0){
            if(res.first != -1) return std::make_pair(-1, -1);
            res.first = i;
        }
        if(acnt[i] < 0) res.second = i;
    }
    return res;
}
 
std::vector<int> solve(
    const nachia::AdjacencyList& T1,
    int root1,
    const nachia::AdjacencyList& T2,
    int root2
){
    int n = T1.num_vertices();
    std::vector<std::pair<int,int>> edges;
    for(int u=0; u<n; u++) for(int v : T1[u]) if(u < v) edges.push_back(std::make_pair(1+u, 1+v));
    for(int u=0; u<n-1; u++) for(int v : T2[u]) if(u < v) edges.push_back(std::make_pair(1+n+u, 1+n+v));
    edges.push_back(std::make_pair(0, 1 + root1));
    edges.push_back(std::make_pair(0, 1 + n + root2));
 
    auto stat = nachia::AHUAlgorithmLinearTime(nachia::AdjacencyList(n*2, edges, true));
    int p1 = 1 + root1, p2 = 1 + n + root2;
    std::vector<int> track;
    
    std::vector<int> ans(n, 0);
 
    while(true){
        std::vector<int> c1(stat.children_ordered[p1].begin(), stat.children_ordered[p1].end());
        for(int& c : c1) c = stat.compressed[c];
        std::vector<int> c2(stat.children_ordered[p2].begin(), stat.children_ordered[p2].end());
        for(int& c : c2) c = stat.compressed[c];
        auto [diff1, diff2] = one_difference(c1, c2);
        if(diff1 == -1) return std::vector<int>(n, 0);
        track.push_back(diff1);
        if(diff2 == -1) break;
        
        for(auto u : stat.children_ordered[p1]) if(stat.compressed[u] == diff1){ p1 = u; break; }
        for(auto u : stat.children_ordered[p2]) if(stat.compressed[u] == diff2){ p2 = u; break; }
    }
 
    std::vector<int> cand_bfs = { 1 + root1 };
    for(int c : track){
        std::vector<int> nx;
        for(int p : cand_bfs) for(int q : stat.children_ordered[p]){
            if(stat.compressed[q] != c) continue;
            nx.push_back(q);
        }
        std::swap(cand_bfs, nx);
    }
    for(int p : cand_bfs) ans[p-1] = 1;
    return ans;
}
 
 
int main(){
    int n; std::cin >> n;
    nachia::AdjacencyList T1, T2;
    
    {
        std::vector<std::pair<int,int>> edges(n);
        for(int i=0; i<n; i++){
            int u; std::cin >> u; u--;
            edges[i] = std::make_pair(i, u);
        }
        T1 = nachia::AdjacencyList(n+1, edges, true);
    }
    {
        std::vector<std::pair<int,int>> edges(n-1);
        for(int i=0; i<n-1; i++){
            int u; std::cin >> u; u--;
            edges[i] = std::make_pair(i, u);
        }
        T2 = nachia::AdjacencyList(n, edges, true);
    }
 
    std::vector<int> ans(n+1);
 
    for(int c1 : nachia::UnitTreeCenter(T1)){
        for(int c2 : nachia::UnitTreeCenter(T2)){
            std::vector<int> res = solve(T1, c1, T2, c2);
            for(int i=0; i<n+1; i++) ans[i] |= res[i];
        }
    }
 
    bool to_be_spaced = false;
    for(int i=0; i<n+1; i++) if(ans[i]){
        if(to_be_spaced) std::cout << ' ';
        std::cout << (i+1);
        to_be_spaced = true;
    }
    std::cout << '\n';
 
    return 0;
}
 
 
struct ios_do_not_sync{
    ios_do_not_sync(){
        std::ios::sync_with_stdio(false);
        std::cin.tie(nullptr);
    }
} ios_do_not_sync_instance;
