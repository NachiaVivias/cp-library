#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_path_sum"
#include "../../../Include/tree/heavylightdecomposition.hpp"

using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;

struct BIT{
  vector<i64> A;
  BIT(int n){
    A.assign(n+1,0);
  }
  void add(int p, i64 x){
    p++;
    while(p < A.size()){
      A[p] += x;
      p += p & -p;
    }
  }
  i64 sum(int r){
    int p = r;
    i64 res = 0;
    while(p > 0){
      res += A[p];
      p -= p & -p;
    }
    return res;
  }
  i64 sum(int l, int r){
    return sum(r) - sum(l);
  }
};

int main() {
  int N,Q; cin >> N >> Q;
  vector<i64> A(N);
  for(int i=0; i<N; i++) cin >> A[i];
  vector<vector<int>> E(N);
  for(int i=0; i<N-1; i++){
    int u,v; cin >> u >> v;
    E[u].push_back(v);
    E[v].push_back(u);
  }

  heavy_light_decomposition hld(E);
  BIT rq(N);

  for(int i=0; i<N; i++) rq.add(hld.idxs()[i],A[i]);

  for(int i=0; i<Q; i++){
    int t; cin >> t;
    if(t == 0){
      int p,x; cin >> p >> x;
      A[p] += x;
      rq.add(hld.idxs()[p],x);
    }
    if(t == 1){
      int u,v; cin >> u >> v;
      int g = hld.lca(u,v);
      i64 res = 0;
      for(auto I : hld.path(g,u)) res += rq.sum(I.first, I.second);
      for(auto I : hld.path(g,v)) res += rq.sum(I.first, I.second);
      res -= A[g];
      cout << res << "\n";
    }
  }
  return 0;
}


struct ios_do_not_sync{
  ios_do_not_sync(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
  }
} ios_do_not_sync_instance;


