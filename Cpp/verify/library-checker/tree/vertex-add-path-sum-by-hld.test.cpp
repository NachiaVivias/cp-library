#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_path_sum"
#include "../../../Include/nachia/tree/heavy-light-decomposition.hpp"

#include <iostream>
#include <cstdint>

struct BIT{
  std::vector<int64_t> A;
  BIT(int n){
    A.assign(n+1,0);
  }
  void add(int p, int64_t x){
    p++;
    while(p < (int)A.size()){
      A[p] += x;
      p += p & -p;
    }
  }
  int64_t sum(int r){
    int p = r;
    int64_t res = 0;
    while(p > 0){
      res += A[p];
      p -= p & -p;
    }
    return res;
  }
  int64_t sum(int l, int r){
    return sum(r) - sum(l);
  }
};

int main() {
  int N,Q; std::cin >> N >> Q;
  std::vector<int> A(N);
  for(int i=0; i<N; i++) std::cin >> A[i];
  std::vector<std::vector<int>> E(N);
  for(int i=0; i<N-1; i++){
    int u,v; std::cin >> u >> v;
    E[u].push_back(v);
    E[v].push_back(u);
  }

  nachia::HeavyLightDecomposition hld(E);
  BIT rq(N);

  for(int i=0; i<N; i++) rq.add(hld.to_seq(i),A[i]);

  for(int i=0; i<Q; i++){
    int t; std::cin >> t;
    if(t == 0){
      int p,x; std::cin >> p >> x;
      rq.add(hld.to_seq(p),x);
    }
    if(t == 1){
      int u,v; std::cin >> u >> v;
      int g = hld.lca(u,v);
      int64_t res = 0;
      for(auto I : hld.path(g,u,true)) res += rq.sum(I.first, I.second);
      for(auto I : hld.path(g,v,false)) res += rq.sum(I.first, I.second);
      std::cout << res << "\n";
    }
  }
  return 0;
}


struct ios_do_not_sync{
  ios_do_not_sync(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
  }
} ios_do_not_sync_instance;


